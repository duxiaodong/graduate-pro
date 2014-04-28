#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>
#include "Communicate.h"
#include "node.h"

class GraphicsNodeItem :public Communicate, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	~GraphicsNodeItem();

	// �ڵ�����
	enum NodeItemType {
		No,Junction,Restriction,
		MotorVolumeGraph, NonMotorVolumeGraph, CarVolumeGraph, BusVolumeGraph,  // ������ͼ
		MotorbikeVolumeGraph, TaxiVolumeGraph, TruckVolumeGraph     // ������ͼ
	};

	// ����
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	//set 
	GraphicsNodeItem & setNodeData(Node *);
	GraphicsNodeItem & setGraphType(NodeItemType);
	// ���û�������
	GraphicsNodeItem & setRadius(qreal radius);
	GraphicsNodeItem & setHaveBorder(bool haveBorder);
	GraphicsNodeItem & setBorderColor(QColor borderColor);
	GraphicsNodeItem & setInnerColor(QColor innerColor);
	GraphicsNodeItem & setNodeItemType(NodeItemType);
	// �������ڵ�, ����Ϊ�ھ�
	void checkNeighbour(GraphicsNodeItem*);
	// get
	qreal radius() const;
	QColor borderColor() const;
	QColor innerColor() const;
	Node * nodeData() const;

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
	// �ڵ�����
	NodeItemType mType;

};

#endif // GRAPHICSNODEITEM_H
