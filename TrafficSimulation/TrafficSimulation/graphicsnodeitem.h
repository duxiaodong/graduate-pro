#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H

#include <QGraphicsItem>

class GraphicsNodeItem : public QObject, public QGraphicsItem
{
	Q_OBJECT

public:
	GraphicsNodeItem(QGraphicsItem *parent = 0);
	GraphicsNodeItem(QPointF normPos, QGraphicsItem *parent=0);
	GraphicsNodeItem(QPointF normPos, int no, QGraphicsItem *parent=0);
	~GraphicsNodeItem();

	void setNormPos(QPointF);
	QPointF normPos() const;
	void setNo(int);
	int no() const;
	// ����
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	QRectF boundingRect() const;
	QPainterPath shape() const;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	// ���û�������
	GraphicsNodeItem & setRadius(qreal radius);
	GraphicsNodeItem & setHaveBorder(bool haveBorder);
	GraphicsNodeItem & setBorderColor(QColor borderColor);
	GraphicsNodeItem & setInnerColor(QColor innerColor);
	// �������ڵ�, ����Ϊ�ھ�
	void checkNeighbour(GraphicsNodeItem*);
	// ��ȡ�뾶
	qreal radius() const;
	// ���ñ��item
	GraphicsNodeItem & setNoTextItem(QGraphicsItem*);

	void checkNoItemVisible();

signals:
	void sendNodeInfoToStatus(QString);
	void clearNodeInfoFromStatus();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	

private:
	void init();
	

private:
	QPointF mNormPos;
	int mNo;
	qreal mRadius;
	QColor mBorderColor;
	QColor mInnerColor;
	bool mHaveBorder;
	// ���ڽ��Ľڵ�
	GraphicsNodeItem* mNeignbour;
	qreal mNearestDistance;
	QGraphicsItem* mNoTextItem;

};

#endif // GRAPHICSNODEITEM_H
