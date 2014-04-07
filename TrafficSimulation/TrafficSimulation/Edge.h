#pragma once

#include "node.h"

/*
���ڴ������йص�����, ڸ����Node��ͬ
���������
*/
class Edge
{
public:
	Edge(){};
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
	// set
	Edge & setSourceNode(Node *);
	Edge & setDestNode(Node *);
	Edge & setRoadLevel(uint);


private:
	// ���������ⲿ�����Ľڵ�
	Node * mSourceNode;
	Node * mDestNode;

	uint mRoadLevel;


};

