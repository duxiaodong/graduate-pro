#include "graphicsnodenotextitem.h"

#include "node.h"


GraphicsNodeNoTextItem::GraphicsNodeNoTextItem(GraphicsNodeItem *parent)
	: QGraphicsTextItem(parent)
	, mNeighbour(0)
{
	QGraphicsTextItem::setPlainText(QString::number(parent->nodeData()->no() )  );
	QGraphicsTextItem::setPos(parent->radius()+3, -parent->radius()-10);
	hide(); // ��ʼ����, ������ݽڵ��ľ��뿼����ʾ
	// ��Ⱦ����
	setCacheMode(QGraphicsItem::ItemCoordinateCache);
	setEnabled(false);
}

GraphicsNodeNoTextItem::~GraphicsNodeNoTextItem()
{

}

GraphicsNodeNoTextItem& GraphicsNodeNoTextItem::setNodeData( Node* node )
{
	mNodeData = node;
	return *this;
}

GraphicsNodeNoTextItem& GraphicsNodeNoTextItem::updateNeighbour( GraphicsNodeNoTextItem* item )
{
	if(!mNeighbour)
		mNeighbour = item;
	else
	{
		if(mNodeData->dis(item->nodeData()) < mNodeData->dis(mNeighbour->nodeData()))
			mNeighbour = item;
	}
	return *this;
}

Node * GraphicsNodeNoTextItem::nodeData()
{
	return mNodeData;
}

void GraphicsNodeNoTextItem::updateVisible()
{
	if (mNeighbour && mNodeData->sceneDis(mNeighbour->nodeData())<30)
	{
		hide();
	}
	else
	{
		show();
	}
}
