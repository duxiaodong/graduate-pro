#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include <QGraphicsScene>

#include "DbAdapter.h"

class NodeGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	NodeGraphicsScene(QObject *parent = 0);
	~NodeGraphicsScene();

public slots:	
	void changeSceneRect(int w, int h);
	void zoom(int step, QPointF hoverPos);
	void move(QPointF offset);

private:
	void updateItems();
	QPointF normCoorToSceneCoor(QPointF);
	QPointF sceneCoorToNormCoor(QPointF);
	qreal shorterSceneRectSide(); // ����sceneRect�н϶̵ı�


private:
	DbAdapter mDbAdapter;
	QList<QPointF>* mPointList;

	qreal mRatio;
	QPointF mOffset;
	
};

#endif // NODEGRAPHICSSCENE_H
