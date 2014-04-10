#pragma once

#include "node.h"

/*
���ڴ������йص�����, ڸ����Node��ͬ
���������
*/
class Edge
{
public:
	Edge():mBusNum(0){};
	///////// ��ʹ���в����Ĺ��캯��, ��Ϊ�����޷�ȷ��ÿ����Щ�����Ǳ����
	Edge(const Edge & );
	Edge& operator=(const Edge &);
	bool operator==(const Edge &);
	~Edge(void);

	// get
	Node * sourceNode() const;
	Node * destNode() const;
	uint roadLevel() const;
	QRectF sceneBorder() const;
	qreal length() const;
	qreal motorWayWidth() const;
	qreal nonMotorWayWidth() const;
	bool wayIsolate() const;
	uint roadType() const;
	uint trafficType() const;
	bool inScale() const;
	int id() const;
	int sourceNodeId() const;
	int destNodeId() const;
	int busNum() const;

	// set
	Edge & setSourceNode(Node *);
	Edge & setDestNode(Node *);
	Edge & setRoadLevel(uint);
	Edge & setLength(qreal);
	Edge & setMotorWayWidth(qreal);
	Edge & setNonMotorWayWidth(qreal);
	Edge & setWayIsolate(bool);
	Edge & setRoadType(uint);
	Edge & setTrafficType(uint);
	Edge & setInScale(bool);
	Edge & setId(int);
	Edge & setSourceNodeId(int);
	Edge & setDestNodeId(int);
	Edge & setBusNum(int);
	void addBus();

private:
	// ���������ⲿ�����Ľڵ�
	Node * mSourceNode;
	Node * mDestNode;

	int mId;
	int mSourceNodeId;
	int mDestNodeId;
	uint mRoadLevel;
	qreal mLength;
	qreal mMotorWayWidth;
	qreal mNonMotorWayWidth;
	bool mWayIsolate;
	uint mRoadType;
	uint mTrafficType;
	bool mInScale;
	int mBusNum;

};

