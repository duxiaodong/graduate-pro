#ifndef GRAPHICSNODENOTEXTITEM_H
#define GRAPHICSNODENOTEXTITEM_H

#include <QGraphicsTextItem>
#include "graphicsnodeitem.h"

class Node;

class GraphicsNodeNoTextItem : public QGraphicsTextItem
{

public:
	GraphicsNodeNoTextItem(GraphicsNodeItem *parent );
	~GraphicsNodeNoTextItem();

	//// set
	GraphicsNodeNoTextItem& setNodeData(Node*);
	GraphicsNodeNoTextItem& updateNeighbour(GraphicsNodeNoTextItem*);

	//// get
	Node * nodeData();
	//// ����Ƿ�ɼ�
	void updateVisible();

private:
	Node * mNodeData;
	GraphicsNodeNoTextItem* mNeighbour;
};

#endif // GRAPHICSNODENOTEXTITEM_H
