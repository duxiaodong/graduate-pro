#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>
#include "Communicate.h"
#include "node.h"

class GraphicsNodeItem :public Communicate, public QGraphicsItem
{
	Q_OBJECT

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	~GraphicsNodeItem();

	// ����
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	//set 
	GraphicsNodeItem & setNodeData(Node *);
	// ���û�������
	GraphicsNodeItem & setRadius(qreal radius);
	GraphicsNodeItem & setHaveBorder(bool haveBorder);
	GraphicsNodeItem & setBorderColor(QColor borderColor);
	GraphicsNodeItem & setInnerColor(QColor innerColor);
	// �������ڵ�, ����Ϊ�ھ�
	void checkNeighbour(GraphicsNodeItem*);
	// get
	qreal radius() const;
	QColor borderColor() const;
	QColor innerColor() const;
	Node * nodeData() const;
	// ���ñ��item
	GraphicsNodeItem & setNoTextItem(QGraphicsItem*);

	void checkNoItemVisible();

signals:


protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	

private:
	void init();
	

private:
	Node * mNodeData;
	// ��������
	qreal mRadius; // ��Χ�뾶, �߿���Ϊ1
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	// ���ڽ��Ľڵ�
	GraphicsNodeItem* mNeignbour;
	qreal mNearestDistance;
	QGraphicsItem* mNoTextItem;

};

#endif // GRAPHICSNODEITEM_H
