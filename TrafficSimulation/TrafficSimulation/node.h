
#ifndef NODE
#define  NODE

#include <QtCore>
#include "node.h"

struct NodeWithCoorNo
{
	QPointF mCoor; //����
	int mNo; //���

	NodeWithCoorNo(){};
	NodeWithCoorNo(QPointF, int);
	bool operator==(const NodeWithCoorNo node)const;
};



inline uint qHash(NodeWithCoorNo n, uint seed = 0){
	return 0;
}


qreal length(QPair<NodeWithCoorNo,NodeWithCoorNo> pair);


#endif // !NODE
