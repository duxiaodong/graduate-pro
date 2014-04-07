#ifndef QGRAPHICSEDGETNETITEM_H
#define QGRAPHICSEDGETNETITEM_H

#include <QGraphicsItem>
#include "Edge.h"

class GraphicsEdgetNetItem : public QGraphicsItem
{

public:
	GraphicsEdgetNetItem(QGraphicsItem *parent = 0);
	~GraphicsEdgetNetItem();

	void addEdgeData(Edge*);

	void advance();

	// �����麯��
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QPainterPath shape() const;
	 
	// ���û�ͼ����
	GraphicsEdgetNetItem & setWidth(qreal width);
	GraphicsEdgetNetItem & setBorderColor(QColor borderColor);
	GraphicsEdgetNetItem & setInnerColor(QColor innerColor);
	GraphicsEdgetNetItem & setHaveBorder(bool haveBorder);

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
