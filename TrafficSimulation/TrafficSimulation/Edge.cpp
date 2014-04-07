#include "Edge.h"




Edge::~Edge(void)
{
}

Edge::Edge( const Edge & edge)
{
	// ���Ƶ�ֵַ���������´���ڵ�
	// ��Ϊ�ڵ��Ǳߵ�����, �Ƕ�����, ��û��������, Ҳ��Ӧ�ù���
	mDestNode = edge.mDestNode;
	mSourceNode = edge.mSourceNode;
	mRoadLevel = edge.mRoadLevel;
}

Edge& Edge::operator=( const Edge & edge )
{
	mDestNode = edge.mDestNode;
	mSourceNode = edge.mSourceNode;
	mRoadLevel = edge.mRoadLevel;
	return *this;
}

bool Edge::operator==( const Edge & edge )
{
	return mDestNode==edge.mDestNode
		&& mSourceNode==edge.mSourceNode
		&& mRoadLevel==edge.mRoadLevel
		;
}

Node * Edge::sourceNode() const
{
	return mSourceNode;
}

Node * Edge::destNode() const
{
	return mDestNode;
}

Edge & Edge::setSourceNode( Node * node)
{
	mSourceNode = node;
	return *this;
}

Edge & Edge::setDestNode( Node * node)
{
	mDestNode = node;
	return *this;
}

Edge & Edge::setRoadLevel( uint level )
{
	mRoadLevel = level;
	return *this;
}

uint Edge::roadLevel() const
{
	return mRoadLevel;
}

QRectF Edge::sceneBorder() const
{
	QRectF rect(mSourceNode->coor(), mDestNode->coor());
	return rect.normalized();
}


