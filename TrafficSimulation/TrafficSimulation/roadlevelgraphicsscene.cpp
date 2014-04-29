#include "roadlevelgraphicsscene.h"
#include "Edge.h"
#include "graphicsedgeitem.h"
#include "node.h"
#include "graphicsedgenetitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"
#include <QGraphicsProxyWidget>

RoadLevelGraphicsScene::RoadLevelGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init(); // ����������ǰ����
	addLegend();

}

RoadLevelGraphicsScene::~RoadLevelGraphicsScene()
{

}

void RoadLevelGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsEdgeItem*> edgeIte(mEdgeList);
	GraphicsEdgeItem* tmpEdge;
	QPointF source, dest;
	while (edgeIte.hasNext())
	{
		tmpEdge = edgeIte.next();
		tmpEdge->advance();
	}
	GraphicsEdgeNetItem* tmpNetItem;
	QListIterator<GraphicsEdgeNetItem*> netIte(mEdgeNetList);
	while (netIte.hasNext())
	{
		tmpNetItem = netIte.next();
		tmpNetItem->advance();
	}
}

void RoadLevelGraphicsScene::init()
{
	mInnerColorList << QColor(205,168,232) << QColor(249,126,128) << QColor(255,225,104)
		<< QColor(254,252,193) << QColor(151,189,253) << QColor(139,182,105) 
		<< QColor(250,158,37);
	mBorderColorList << QColor(147,102,128) << QColor(186,98,96) << QColor(231,195,96) 
		<< QColor(221,217,188) << QColor(151,189,253) <<QColor(139,182,105) 
		<< QColor(231,160,37);
	mHaveBorderList << true << true << true << true << false << false << true;
	mWidthList << 7 << 6 << 6 << 5 << 2 << 2 << 9;
	mZValueList << 6 << 4 << 3 << 2 << 1 << 0 << 5; 

}

void RoadLevelGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("���и߼ܵ�·"),LegendElement::THICK_LINE,
		mWidthList.at(0),mInnerColorList.at(0),mBorderColorList.at(0))
		<< LegendElement(QStringLiteral("���п��ٸɵ�"),LegendElement::THICK_LINE,
		mWidthList.at(1),mInnerColorList.at(1),mBorderColorList.at(1))
		<< LegendElement(QStringLiteral("�������ɵ�"),LegendElement::THICK_LINE,
		mWidthList.at(2),mInnerColorList.at(2),mBorderColorList.at(2))
		<< LegendElement(QStringLiteral("���дθɵ�"),LegendElement::THICK_LINE,
		mWidthList.at(3),mInnerColorList.at(3),mBorderColorList.at(3))
		<< LegendElement(QStringLiteral("����֧·"),LegendElement::LINE,
		mWidthList.at(4),mInnerColorList.at(4),mBorderColorList.at(4))
		<< LegendElement(QStringLiteral("������·"),LegendElement::LINE,
		mWidthList.at(5),mInnerColorList.at(5),mBorderColorList.at(5))
		<< LegendElement(QStringLiteral("���ٹ�·"),LegendElement::THICK_LINE,
		mWidthList.at(6),mInnerColorList.at(6),mBorderColorList.at(6))
		;
	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);
}


void RoadLevelGraphicsScene::addItems()
{
	Edge* tmpEdge;
	GraphicsEdgeItem* item;
	QListIterator<Edge*> ite(mEdgeDataList);
	mEdgeNetList << new GraphicsEdgeNetItem << new GraphicsEdgeNetItem << new GraphicsEdgeNetItem 
		<< new GraphicsEdgeNetItem << new GraphicsEdgeNetItem << new GraphicsEdgeNetItem 
		<< new GraphicsEdgeNetItem ;
	GraphicsEdgeNetItem* tmpNetItem;
	while (ite.hasNext())
	{
		tmpEdge = ite.next();
		item = new GraphicsEdgeItem;
		item->setEdgeData(tmpEdge);
		int level = tmpEdge->roadLevel();
		item->setWidth(mWidthList.at(level)).setHaveBorder(false).setInnerColor(mBorderColorList.at(level))
			.setZValue(mZValueList.at(level));
		tmpNetItem = mEdgeNetList[level];
		tmpNetItem->addEdgeData(tmpEdge);
		mEdgeList << item;
		addItem(item);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );

	}// edgenet���edge, scene���edge, ��ȡ��node
	for(int i=0; i<mEdgeNetList.size(); ++i)
	{
		tmpNetItem = mEdgeNetList[i];
		tmpNetItem->setZValue(mZValueList.at(i)+0.5 );
		tmpNetItem->setWidth(mWidthList.at(i)-2 );
		tmpNetItem->setHaveBorder(false);
		tmpNetItem->setInnerColor(mInnerColorList.at(i) );
		addItem(tmpNetItem);
	}
}









