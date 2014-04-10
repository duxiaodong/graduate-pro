#ifndef ROADLEVELGRAPHICSSCENE_H
#define ROADLEVELGRAPHICSSCENE_H

#include "graphicsscene.h"

class Edge;
class GraphicsEdgeItem;
class GraphicsEdgetNetItem;

class RoadLevelGraphicsScene :public GraphicsScene
{
	Q_OBJECT

public:
	RoadLevelGraphicsScene(QObject *parent = 0);
	~RoadLevelGraphicsScene();

	void addItems();

private:
	void updateItems();
	void doSomething(){};
	void init();
	void addLegend();
	
private:
	
	QList<GraphicsEdgeItem*> mEdgeList;
	QList<GraphicsEdgetNetItem*> mEdgeNetList;

	// ����·����ɫ�Ϳ��
	// ����list���ϸ��յ�·�ȼ���˳��
	QList<bool> mHaveBorderList;
	QList<QColor> mInnerColorList;
	QList<QColor> mBorderColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;

};

#endif // ROADLEVELGRAPHICSSCENE_H
