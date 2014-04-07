#include "graphicsnodenotextitem.h"

GraphicsNodeNoTextItem::GraphicsNodeNoTextItem(GraphicsNodeItem *parent)
	: QGraphicsTextItem(parent)
{
	parent->setNoTextItem(this);
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
