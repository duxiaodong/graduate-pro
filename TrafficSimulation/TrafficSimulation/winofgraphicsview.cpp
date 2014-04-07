#include "winofgraphicsview.h"

#include "nodegraphicsscene.h"
#include "roadlevelgraphicsscene.h"
#include "graphicsview.h"
#include <QGraphicsView>
#include <QGLWidget>
#include <QPrinter>
#include <QPrintDialog>


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
{
	ui.setupUi(this);

	initStatusBar();

	NodeGraphicsScene* scene = new NodeGraphicsScene;
	//RoadLevelGraphicsScene* scene = new RoadLevelGraphicsScene;
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




