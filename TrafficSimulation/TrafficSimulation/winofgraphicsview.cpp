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
#include "structsfordb.h"


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
{
	ui.setupUi(this);

	initStatusBar();

	loadDataFromDb(); // ����������֮ǰ

	//NodeGraphicsScene* scene = new NodeGraphicsScene;
	//RoadLevelGraphicsScene* scene = new RoadLevelGraphicsScene;
	BusNumGraphicsScene* scene = new BusNumGraphicsScene;
	scene->setEdgeDataList(mEdgeDataList).setNodeDataList(mNodeDataList).addItems();
	mView = new GraphicsView(scene);
	connect(scene, SIGNAL(sendMsgToStatus(QString)), this, SLOT(updateStatus(QString)) );
	connect(scene, SIGNAL(clearMsgFromStatus()), this, SLOT(clearTmpMsgFromStatus())  );

	updatePermanentStatus(QStringLiteral("�ڵ���Ŀ��")+QString::number(scene->nodeNum()),
		QStringLiteral("·����Ŀ��")+QString::number(scene->edgeNum()) );

	setWindowTitle(QStringLiteral("��ͨ�����ɹ����ӻ�") );
	showMaximized();
	setCentralWidget(mView);

	 initActions(); // warning: ���� initToolBar֮ǰ
	 initToolBar(); // warning: ����mView�ĳ�ʼ��֮��

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
	mPrintAction = new QAction("Print", this);
	mPrintAction->setStatusTip("Print view");
	connect(mPrintAction, SIGNAL(triggered()),mView, SLOT(print()) );

}

void WinOfGraphicsView::initToolBar()
{
	mToolBar = addToolBar("toolbar");
	mToolBar->addAction(mPrintAction);
}

void WinOfGraphicsView::loadDataFromDb()
{
	mNodeDataList = mDbAdapter.loadNormNodes();
	mEdgeDataList = mDbAdapter.loadEdges();
	mBusRouteList = mDbAdapter.loadBusRoutes();
	
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


}




