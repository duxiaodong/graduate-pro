#include "winofgraphicsview.h"

#include "nodegraphicsscene.h"
#include "roadlevelgraphicsscene.h"
#include "busnumgraphicsscene.h"
#include "graphicsview.h"
#include <QGraphicsView>
#include <QGLWidget>
#include <QPrinter>
#include <QPrintDialog>
#include "BusRoute.h"
#include "RoadPermission.h"
#include "structsfordb.h"
#include "junctiontypegraphicsscene.h"
#include "TurnRestrict.h"
#include "turnrestrictgraphicsscene.h"
#include "roadtypegraphicsscene.h"
#include "trafficmanagegraphicsscene.h"
#include "trafficforbidgraphicsscene.h"
#include "trafficnumlimitgraphicsscene.h"
#include <QFileDialog>
#include "commonexception.h"
#include "pathnotexistsexception.h"
#include "TrafficVolume.h"
#include "trafficroadvolumegraphicsscene.h"
#include "trafficnodevolumegraphicsscene.h"
#include "Capability.h"
#include "trafficnodecapabilitygraphicsscene.h"
#include "trafficroadcapabilitygraphicsscene.h"
#include "Speed.h"
#include "speedgraphicsscene.h"


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
	, mScene(0)
	, mSelectWidget(0)
{
	ui.setupUi(this);

	initStatusBar();

	//loadDataFromDb(); // ����������֮ǰ

	mView = new GraphicsView;
	setCentralWidget(mView);

	setWindowTitle(QStringLiteral("��ͨ�����ɹ����ӻ�") );
	showMaximized();
	setCentralWidget(mView);

	initActions(); // warning: ���� initToolBar֮ǰ
	initToolBar(); // warning: ����mView�ĳ�ʼ��֮��

	if (!mSelectWidget)
	{
		mSelectWidget = new SelectGraphicsWidget(this);
		connect(mSelectWidget, SIGNAL(selectGraphics(int,int)),this,SLOT(changeScene(int,int)) );
	}
	
}

WinOfGraphicsView::~WinOfGraphicsView()
{

}

void WinOfGraphicsView::updateStatus( QString msg )
{
	statusBar()->showMessage(msg);

}

void WinOfGraphicsView::clearTmpMsgFromStatus()
{
	statusBar()->clearMessage();
}

void WinOfGraphicsView::initStatusBar()
{
	mStatusLabel1 = new QLabel;
	mStatusLabel2 = new QLabel;
	statusBar()->addPermanentWidget(mStatusLabel1);
	statusBar()->addPermanentWidget(mStatusLabel2);
}

void WinOfGraphicsView::updatePermanentStatus(QString str1, QString str2)
{
	mStatusLabel1->setText(str1+"    ");
	mStatusLabel2->setText(str2+"    ");
}

void WinOfGraphicsView::initActions()
{
	mSelectSceneAction = new QAction("Open", this);
	mSelectSceneAction->setStatusTip("select graphic");
	connect(mSelectSceneAction, SIGNAL(triggered()),this, SLOT(selectGraphics()));
	mPrintAction = new QAction("Print", this);
	mPrintAction->setStatusTip("Print view");
	connect(mPrintAction, SIGNAL(triggered()),mView, SLOT(print()) );
	mCreateDbAction = new QAction("Create db", this);
	connect(mCreateDbAction, SIGNAL(triggered()), this, SLOT(createDb()));
	mSelectDbAction = new QAction("Select db",this);
	connect(mSelectDbAction, SIGNAL(triggered()), this, SLOT(selectDb()));
	
}

void WinOfGraphicsView::initToolBar()
{
	mToolBar = addToolBar("toolbar");
	mToolBar->addAction(mSelectSceneAction);
	mToolBar->addAction(mPrintAction);
	mToolBar->addAction(mCreateDbAction);
	mToolBar->addAction(mSelectDbAction);
}

void WinOfGraphicsView::loadDataFromDb()
{
	mNodeDataList = mDbAdapter.loadNormNodes();
	mEdgeDataList = mDbAdapter.loadEdges();
	mBusRouteList = mDbAdapter.loadBusRoutes();
	mTurnRestrictionList = mDbAdapter.loadTurnRestrictions();
	mRoadForbidList = mDbAdapter.loadTrafficForbid();
	mRoadNumLimitList = mDbAdapter.loadTrafficNumLimit();
	mNodeTrafficVolumeList = mDbAdapter.loadNodeTrafficVolume();
	mRoadTrafficVolumeList = mDbAdapter.loadRoadTrafficVolume();
	mNodeCapabilityList = mDbAdapter.loadNodeCapability();
	mRoadCapabilityList = mDbAdapter.loadRoadCapability();
	mSpeedList = mDbAdapter.loadSpeed();
	
	{  ///// ��Edge�е�Node��ʼ��
		QHash<int,Node*> idNodeHash;
		Node * tmpNode;
		QListIterator<Node*> nodeIte(mNodeDataList);
		while (nodeIte.hasNext())
		{
			tmpNode = nodeIte.next();
			idNodeHash.insert(tmpNode->id(), tmpNode);
		}
		Edge * tmpEdge;
		QListIterator<Edge*> edgeIte(mEdgeDataList);
		int sourceNodeId;
		int destNodeId;
		while (edgeIte.hasNext())
		{
			tmpEdge = edgeIte.next();
			sourceNodeId = tmpEdge->sourceNodeId();
			destNodeId = tmpEdge->destNodeId();
			tmpEdge->setDestNode(idNodeHash.value(destNodeId));
			tmpEdge->setSourceNode(idNodeHash.value(sourceNodeId));
		}

	} //// ��Edge�е�Node��ʼ��

	{ ///// ����ÿ��·���ϵĹ���·������
		Edge * tmpEdge;
		QHash<TwoInt, Edge*> nopairEdgeHash;
		QListIterator<Edge*> edgeIte(mEdgeDataList);
		while (edgeIte.hasNext())
		{
			tmpEdge = edgeIte.next();
			TwoInt pk(tmpEdge->sourceNode()->no(), tmpEdge->destNode()->no());
			nopairEdgeHash.insert(pk, tmpEdge);
		}
		QListIterator<BusRoute*> routeIte(mBusRouteList);
		QList<int> stops;
		BusRoute* tmpRoute;
		while (routeIte.hasNext())
		{
			tmpRoute = routeIte.next();
			stops = tmpRoute->stops();
			for(int i=0; i<stops.size()-1; ++i)
			{
				tmpEdge = nopairEdgeHash.value(TwoInt(stops.at(i), stops.at(i+1)));
				if(tmpEdge)
					tmpEdge->addBus();
			};
		}

	} ////// ��ɼ���ÿ����·�ϵĹ�������

	{ ///// ���� id-nodeӳ��
		//// �ڵ��Ƿ�������ת���
		QHash<int,Node*> idNodeHash;
		QListIterator<Node*> nodeDataIte(mNodeDataList);
		Node * tmpNode;
		while (nodeDataIte.hasNext())
		{
			tmpNode = nodeDataIte.next();
			idNodeHash.insert(tmpNode->id(), tmpNode);
		}
		QListIterator<TurnRestrict*> turnIte(mTurnRestrictionList);
		TurnRestrict * restr;
		while (turnIte.hasNext())
		{
			restr = turnIte.next();
			tmpNode = idNodeHash.value(restr->currentNodeNo());
			tmpNode->setHaveTurnRestrict(true);
		}
		///// ��ͨ��
		QListIterator<TrafficVolume*> volumeIte(mNodeTrafficVolumeList);
		TrafficVolume* tmpVolume;
		while (volumeIte.hasNext())
		{
			tmpVolume = volumeIte.next();
			tmpNode = idNodeHash.value(tmpVolume->id());
			tmpNode->setTrafficVolume(tmpVolume);
		}
		//// ��ͨ������
		QListIterator<Capability*> capabilityIte(mNodeCapabilityList);
		Capability* tmpCapability;
		while (capabilityIte.hasNext())
		{
			tmpCapability = capabilityIte.next();
			tmpNode = idNodeHash.value(tmpCapability->id());
			tmpNode->setTrafficCapability(tmpCapability);
		}

	}

	{ ///// ������ id-edge ӳ��
		//// road���ö�Ӧ�Ľ���
		///// road ������Ӧ���޺�ͨ��
		QHash<int, Edge*> idEdgeHash;
		QListIterator<Edge*> edgeIte(mEdgeDataList);
		Edge* tmpEdgeData;
		while (edgeIte.hasNext())
		{
			tmpEdgeData = edgeIte.next();
			idEdgeHash.insert(tmpEdgeData->id(), tmpEdgeData);
		}
		QListIterator<RoadPermission*> forbidIte(mRoadForbidList);
		RoadPermission* tmpForbid;
		while (forbidIte.hasNext())
		{
			tmpForbid = forbidIte.next();
			tmpEdgeData = idEdgeHash.value(tmpForbid->roadId());
			tmpEdgeData->setTrafficForbid(tmpForbid);
		}
		QListIterator<RoadPermission*> numLimitIte(mRoadNumLimitList);
		RoadPermission* tmpLimit;
		while (numLimitIte.hasNext())
		{
			tmpLimit = numLimitIte.next();
			tmpEdgeData = idEdgeHash.value(tmpLimit->roadId());
			tmpEdgeData->setTrafficNumLimit(tmpLimit);
		}
		//// ���ý�ͨ��
		QListIterator<TrafficVolume*> volumeIte(mRoadTrafficVolumeList);
		TrafficVolume* tmpVolume;
		while (volumeIte.hasNext())
		{
			tmpVolume = volumeIte.next();
			tmpEdgeData = idEdgeHash.value(tmpVolume->id());
			tmpEdgeData->setTrafficVolume(tmpVolume);
		}
		///// ���ó�����
		QListIterator<Capability*> capabilityIte(mRoadCapabilityList);
		Capability* tmpCapability;
		while (capabilityIte.hasNext())
		{
			tmpCapability = capabilityIte.next();
			tmpEdgeData = idEdgeHash.value(tmpCapability->id());
			tmpEdgeData->setTrafficCapability(tmpCapability);
		}
		/////  ·�γ���
		QListIterator<Speed*> speedIte(mSpeedList);
		Speed* tmpSpeed;
		while (speedIte.hasNext())
		{
			tmpSpeed = speedIte.next();
			tmpEdgeData = idEdgeHash.value(tmpSpeed->id());
			tmpEdgeData->setSpeed(tmpSpeed);
		}

	}

}

void WinOfGraphicsView::changeScene( int index1, int index2 )
{
	switch (index1)
	{
	case 0:
		switch (index2)
		{
		case 0:
			mScene = new RoadLevelGraphicsScene;
			mScene->setTitle(QStringLiteral("��·����ȼ��ֲ�"));
			break;
		case 1:
			mScene = new NodeGraphicsScene;
			mScene->setTitle(QStringLiteral("��·����ڵ���"));
			break;
		case 2:
			mScene = new BusNumGraphicsScene;
			mScene->setTitle(QStringLiteral("������ͨ�����ֲ�"));
		default:
			break;
		}
		break;
	case 1:
		switch (index2)
		{
		case 0:
			mScene = new JunctionTypeGraphicsScene;
			mScene->setTitle(QStringLiteral("��������ͷֲ�"));
			break;
		case 1:
			mScene = new TurnRestrictGraphicsScene;
			mScene->setTitle(QStringLiteral("ת�����ƽ���ڷֲ�"));
			break;
		case 2:
			mScene = new RoadTypeGraphicsScene;
			mScene->setTitle(QStringLiteral("��·���͹�����Ϣ"));
			break;
		case 3:
			mScene = new TrafficManageGraphicsScene;
			mScene->setTitle(QStringLiteral("��·��ͨ����"));
		case 4:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::BikeForbid);
			mScene->setTitle(QStringLiteral("���г���ֹͨ������ֲ�"));
			break;
		case 5:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::CarForbid);
			mScene->setTitle(QStringLiteral("�ͳ���ֹͨ������ֲ�"));
			break;
		case 6:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::MotorForbid);
			mScene->setTitle(QStringLiteral("Ħ�г���ֹͨ������ֲ�"));
			break;
		case 7:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::TaxiForbid);
			mScene->setTitle(QStringLiteral("���⳵��ֹͨ������ֲ�"));
			break;
		case 8:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::BusForbid);
			mScene->setTitle(QStringLiteral("��������ֹͨ������ֲ�"));
			break;
		case 9:
			mScene = new TrafficForbidGraphicsScene;
			((TrafficForbidGraphicsScene*) mScene)->setForbidType(TrafficForbidGraphicsScene::TruckForbid);
			mScene->setTitle(QStringLiteral("������ֹͨ������ֲ�"));
			break;
		case 10:
			mScene = new TrafficNumLimitGraphicsScene;
			((TrafficNumLimitGraphicsScene*) mScene)->setLimitType(TrafficNumLimitGraphicsScene::CarLimit);
			mScene->setTitle(QStringLiteral("�ͳ��޺�ͨ������ֲ�"));
			break;
		case 11:
			mScene = new TrafficNumLimitGraphicsScene;
			((TrafficNumLimitGraphicsScene*) mScene)->setLimitType(TrafficNumLimitGraphicsScene::MotorLimit);
			mScene->setTitle(QStringLiteral("Ħ�г��޺�ͨ������ֲ�"));
			break;
		case 12:
			mScene = new TrafficNumLimitGraphicsScene;
			((TrafficNumLimitGraphicsScene*) mScene)->setLimitType(TrafficNumLimitGraphicsScene::TaxiLimit);
			mScene->setTitle(QStringLiteral("���⳵�޺�ͨ������ֲ�"));
			break;
		case 13:
			mScene = new TrafficNumLimitGraphicsScene;
			((TrafficNumLimitGraphicsScene*) mScene)->setLimitType(TrafficNumLimitGraphicsScene::TruckLimit);
			mScene->setTitle(QStringLiteral("�����޺�ͨ������ֲ�"));
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (index2)
		{
		case 0:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::MotorVolume);
			mScene->setTitle(QStringLiteral("������·�ν�ͨ���ֲ�"));
			break;
		case 1:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::MotorVolume);
			mScene->setTitle(QStringLiteral("����������ڽ�ͨ���ֲ�"));
			break;
		case 2:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::NonMotorVolume);
			mScene->setTitle(QStringLiteral("�ǻ�����·�ν�ͨ���ֲ�"));
			break;
		case 3:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::NonMotorVolume);
			mScene->setTitle(QStringLiteral("�ǻ���������ڽ�ͨ���ֲ�"));
			break;
		case 4:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::CarVolume);
			mScene->setTitle(QStringLiteral("�ͳ�·�ν�ͨ���ֲ�"));
			break;
		case 5:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::BusVolume);
			mScene->setTitle(QStringLiteral("������·�ν�ͨ���ֲ�"));
			break;
		case 6:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::MotorbikeVolume);
			mScene->setTitle(QStringLiteral("Ħ�г�·�ν�ͨ���ֲ�"));
			break;
		case 7:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::TruckVolume);
			mScene->setTitle(QStringLiteral("����·�ν�ͨ���ֲ�"));
			break;
		case 8:
			mScene = new TrafficRoadVolumeGraphicsScene;
			((TrafficRoadVolumeGraphicsScene*)mScene)->setVolumeType(TrafficRoadVolumeGraphicsScene::TaxiVolume);
			mScene->setTitle(QStringLiteral("���⳵·�ν�ͨ���ֲ�"));
			break;
		case 9:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::CarVolume);
			mScene->setTitle(QStringLiteral("�ͳ�����ڽ�ͨ���ֲ�"));
			break;
		case 10:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::BusVolume);
			mScene->setTitle(QStringLiteral("����������ڽ�ͨ���ֲ�"));
			break;
		case 11:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::MotorbikeVolume);
			mScene->setTitle(QStringLiteral("Ħ�г�����ڽ�ͨ���ֲ�"));
			break;
		case 12:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::TruckVolume);
			mScene->setTitle(QStringLiteral("��������ڽ�ͨ���ֲ�"));
			break;
		case 13:
			mScene = new TrafficNodeVolumeGraphicsScene;
			((TrafficNodeVolumeGraphicsScene*)mScene)->setVolumeType(TrafficNodeVolumeGraphicsScene::TaxiVolume);
			mScene->setTitle(QStringLiteral("���⳵����ڽ�ͨ���ֲ�"));
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (index2)
		{
		case 0:
			mScene = new TrafficRoadCapabilityGraphicsScene;
			((TrafficRoadCapabilityGraphicsScene*)mScene)->setCapabilityType(TrafficRoadCapabilityGraphicsScene::MotorCapability);
			mScene->setTitle(QStringLiteral("������·�ν�ͨ���ɷֲ�"));
			break;
		case 1:
			mScene = new TrafficNodeCapabilityGraphicsScene;
			((TrafficNodeCapabilityGraphicsScene*)mScene)->setCapabilityType(TrafficNodeCapabilityGraphicsScene::MotorCapability);
			mScene->setTitle(QStringLiteral("����������ڽ�ͨ���ɷֲ�"));
			break;
		case 2:
			mScene = new TrafficRoadCapabilityGraphicsScene;
			((TrafficRoadCapabilityGraphicsScene*)mScene)->setCapabilityType(TrafficRoadCapabilityGraphicsScene::NonMotorCapability);
			mScene->setTitle(QStringLiteral("�ǻ�����·�ν�ͨ���ɷֲ�"));
			break;
		case 3:
			mScene = new TrafficNodeCapabilityGraphicsScene;
			((TrafficNodeCapabilityGraphicsScene*)mScene)->setCapabilityType(TrafficNodeCapabilityGraphicsScene::MotorCapability);
			mScene->setTitle(QStringLiteral("����������ڽ�ͨ���ɷֲ�"));
			break;
		case 4:
			mScene = new SpeedGraphicsScene;
			mScene->setTitle(QStringLiteral("������·��ƽ�����ٷֲ�"));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	mScene->setEdgeDataList(mEdgeDataList).setNodeDataList(mNodeDataList).addItems();
	connect(mScene, SIGNAL(sendMsgToStatus(QString)), this, SLOT(updateStatus(QString)) );
	connect(mScene, SIGNAL(clearMsgFromStatus()), this, SLOT(clearTmpMsgFromStatus())  );
	updatePermanentStatus(QStringLiteral("�ڵ���Ŀ��")+QString::number(mScene->nodeNum()),
		QStringLiteral("·����Ŀ��")+QString::number(mScene->edgeNum()) );
	mView->setScene(mScene);
}

void WinOfGraphicsView::showEvent( QShowEvent * evt )
{
	if (!mSelectWidget)
	{
		mSelectWidget = new SelectGraphicsWidget(this);
		connect(mSelectWidget, SIGNAL(selectGraphics(int,int)),this,SLOT(changeScene(int,int)) );
	}
	//if(!mScene)
	//	mSelectWidget->show();
	QMainWindow::showEvent(evt);
}

void WinOfGraphicsView::selectGraphics()
{
	mSelectWidget->show();
}

void WinOfGraphicsView::createDb()
{
	try{
		QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("��ѡ�������ļ�����·��"));
		DB db;
		db.setFileDir(path);
		QDir dir(path);
		db.setCreateDbName(dir.dirName()+".db");
		db.createTablesAndFetchData();
	}
	catch(CommonException & e){
		qDebug() << e.info();
	}
	catch(PathNotExistsException & e){
		qDebug() << e.what();
	}
	catch(QException){
		qDebug() << "error!!";
	}
	QMessageBox::information(this, QStringLiteral("���ݿⴴ���ɹ�"), QStringLiteral("���ݿⴴ���ɹ�"),QMessageBox::Yes );
}

void WinOfGraphicsView::selectDb()
{
	QString filepath = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ�����ݿ�"));
	if (!filepath.isNull())
	{
		mDbAdapter.setDbPath(filepath);
		loadDataFromDb();
	}
	
}




