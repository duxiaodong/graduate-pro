#ifndef GRAPHICSSIDELINEITEM_H
#define GRAPHICSSIDELINEITEM_H

#include <QGraphicsItem>
#include <QColor>
#include "Communicate.h"
class Edge;

/*
��һ�߲��lineitem, ����˫��ĵ�·ÿһ��

*/
class GraphicsSideLineItem :public Communicate, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	GraphicsSideLineItem(QGraphicsItem *parent=0);
	~GraphicsSideLineItem();

	// graph type
	enum GraphType
	{
		RoadTypeGraph, TrafficTypeGraph, BusNumGraph, RoadLevelGraph,
		BikeForbidGraph, CarForbidGraph, MotorForbidGraph,  // ��������ͼ
		BusForbidGraph, TaxiForbidGraph, TruckForbidGraph,  // ��������ͼ
		CarLimitGraph, TaxiLimitGraph, TruckLimitGraph, MotorLimitGraph,  // �޺�ͨ������ͼ
		MotorVolumeGraph, NonMotorVolumeGraph, CarVolumeGraph, BusVolumeGraph,  // ������ͼ
		MotorbikeVolumeGraph, TaxiVolumeGraph, TruckVolumeGraph,     // ������ͼ
		MotorCapabilityGraph, NonMotorCapabilityGraph, // ������
		SpeedGraph,  // ƽ���ٶ�
	};

	// set
	GraphicsSideLineItem & setEdgeData(Edge*);
	GraphicsSideLineItem & setWidth(qreal);
	GraphicsSideLineItem & setColor(QColor);
	GraphicsSideLineItem & setGraphType(GraphType);

	void advance();
	Edge* edgeData() const;
	void updateAttr(QColor, qreal);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
	void init();

private:
	Edge* mEdgeData;
	//  ��������
	QColor mColor;
	qreal mWidth;
	// ��·����
	GraphType mGraphType;
	
};

#endif // GRAPHICSSIDELINEITEM_H
