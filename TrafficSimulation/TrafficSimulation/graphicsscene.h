#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "DbAdapter.h"

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(QObject *parent = 0);
	~GraphicsScene();

public slots:	
	void changeSceneRect(int w, int h);
	void zoom(int step, QPointF hoverPos);
	void move(QPointF offset);

signals:
	void sendMsgToStatus(QString);
	void clearMsgFromStatus();

protected:
	virtual void updateItems()=0;
	virtual void moveItems(){};
	QPointF normCoorToSceneCoor(QPointF);
	QPointF sceneCoorToNormCoor(QPointF);
	qreal shorterSceneRectSide(); // ����sceneRect�н϶̵ı�

	virtual void checkNoTextVisible() = 0;
	
	void drawBackground(QPainter *painter, const QRectF &rect);

protected:
	DbAdapter mDbAdapter;

private:
	qreal mRatio;
	QPointF mOffset;

	QColor mBackColor;

};

#endif // GRAPHICSSCENE_H
