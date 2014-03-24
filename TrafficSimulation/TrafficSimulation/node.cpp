#include "node.h"
#include <QtMath>

// ����λ�úͱ����Ϣ�Ľڵ�
NodeWithCoorNo::NodeWithCoorNo( QPointF p, int no)
{
	mCoor = p;
	mNo = no;
}

bool NodeWithCoorNo::operator==( const NodeWithCoorNo node ) const
{
	return (this->mCoor==node.mCoor) && (this->mNo==node.mNo);
}


qreal length( QPair<NodeWithCoorNo,NodeWithCoorNo> pair )
{
	QPointF p1 = pair.first.mCoor;
	QPointF p2 = pair.second.mCoor;
	QPointF delta = p1 - p2;
	return qSqrt(qPow(delta.x(),2)+qPow(delta.y(),2));

}
