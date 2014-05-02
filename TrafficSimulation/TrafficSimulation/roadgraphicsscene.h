#ifndef ROADGRAPHICSSCENE_H
#define ROADGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;
class RoadGraphicsConfigDialog;
class LegendProxy;

class RoadGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	RoadGraphicsScene(QObject *parent=0);
	~RoadGraphicsScene();

	virtual void addItems()=0;

public slots:
	void config();

signals:
	void updateView();

protected:
	virtual void init()=0;
	virtual void addLegend()=0;
	virtual void updateItems();
	virtual void updateItemsAttr(){};


	QList<GraphicsSideLineItem*> mSideLineItemList;
	// ��������
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
	QList<QString> mLabelTextList;
	// ���ô���
	RoadGraphicsConfigDialog* mConfigDialog;
	// ͼ��
	LegendProxy* mLegendProxy;

	
};

#endif // ROADGRAPHICSSCENE_H
