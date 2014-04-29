#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgeNetItem : public QGraphicsItem
{

public:
	GraphicsEdgeNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgeNetItem();

	void addEdgeData(Edge*);

	void advance();

	// �����麯��
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QPainterPath shape() const;
	 
	// ���û�ͼ����
	GraphicsEdgeNetItem & setWidth(qreal width);
	GraphicsEdgeNetItem & setBorderColor(QColor borderColor);
	GraphicsEdgeNetItem & setInnerColor(QColor innerColor);
	GraphicsEdgeNetItem & setHaveBorder(bool haveBorder);

	qreal edgeWidth() const ;
	QColor innerColor() const;
	QColor borderColor() const;

private:
	void init();

private:
	QList<Edge*> mEdgeDataList;
	// ��ͼ����
	qreal mEdgeWidth;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	
};

#endif // QGRAPHICSEDGETNETITEM_H
