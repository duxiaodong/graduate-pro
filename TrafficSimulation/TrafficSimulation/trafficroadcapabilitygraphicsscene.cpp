#include "trafficroadcapabilitygraphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "Capability.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


TrafficRoadCapabilityGraphicsScene::TrafficRoadCapabilityGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficRoadCapabilityGraphicsScene::~TrafficRoadCapabilityGraphicsScene()
{

}

TrafficRoadCapabilityGraphicsScene& TrafficRoadCapabilityGraphicsScene::setCapabilityType(CapabilityType type)
{
	mCapabilityType = type;
	return *this;
}

void TrafficRoadCapabilityGraphicsScene::addItems()
{

	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge* tmpEdgeData;
	qreal volume;
	GraphicsSideLineItem * item;
	int index;
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		item = new GraphicsSideLineItem;
		switch (mCapabilityType)
		{
		case TrafficRoadCapabilityGraphicsScene::MotorCapability:
			volume = tmpEdgeData->trafficCapability()->motorCapability();
			item->setGraphType(GraphicsSideLineItem::MotorVolumeGraph);
			break;
		case TrafficRoadCapabilityGraphicsScene::NonMotorCapability:
			volume = tmpEdgeData->trafficCapability()->nonMotorCapability();
			item->setGraphType(GraphicsSideLineItem::NonMotorVolumeGraph);
			break;
		default:
			break;
		}
		if(volume<=0.4)
			index = 0;
		else if(volume<=0.6)
			index = 1;
		else if(volume<=0.75)
			index = 2;
		else if(volume<=0.90)
			index = 3;
		else if(volume<=1)
			index = 4;
		else
			index = 5;

		item->setEdgeData(tmpEdgeData).setColor(mColorList.at(index)).setWidth(mWidthList.at(index))
			.setZValue(mZValueList.at(index));
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);

	}
}

void TrafficRoadCapabilityGraphicsScene::init()
{
	mColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40);
	mWidthList << 3 << 3 << 3 << 3 << 3 << 3;
	mZValueList << 1 << 2 << 3 << 4 << 5 << 6;
}

void TrafficRoadCapabilityGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement("<=0.40", LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement("0.40-0.60", LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement("0.60-0.75", LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement("0.75-0.90", LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement("0.90-1.00", LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(">=1.00", LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	Legend* legend = new Legend(elements);
	LegendProxy* proxy = new LegendProxy(legend);
	addItem(proxy);
}

void TrafficRoadCapabilityGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsSideLineItem*> ite(mSideLineItemList);
	GraphicsSideLineItem* item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->advance();
	}
}
