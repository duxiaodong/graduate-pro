
#ifndef NODE
#define  NODE

#include <QtCore>
#include "node.h"
#include "Normal.h"

class Positionable{
public:
	virtual QPointF coor() const = 0;
	virtual void setCoor(const QPointF& p) = 0;
};
/*
���ڴ����ڵ���ص�����
�ҷǳ�ڸ�������, ��Ϊ��ͨ�����˷��ڴ��, ��Ϊ���ض��龰��ֻ�õ����к��ٵ���Ϣ
*/
class Node
	: virtual public Normal
{
public:
	Node();
	Node(const Node & );
	Node & operator = (const Node & );
	Node(QPointF, int);
	bool operator==(const Node & node)const;

	Rect border() const;
	void norm(qreal, QPointF);

	// get
	QPointF coor() const;
	int id() const;
	int no() const;
	QPointF sceneCoor() const;
	int junctionType() const;
	bool inScale() const;
	bool haveTurnRestrict();
	// set
	Node& setCoor(QPointF);
	Node& setNo(int);
	Node& setSceneCoor(QPointF);
	Node& setJunctionType(int);
	Node& setInScale(bool);
	Node& setId(int);
	Node& setHaveTurnRestrict(bool);
	// ���������node����
	qreal dis(Node*)const;
	qreal sceneDis(Node*)const;
	

private:
	QPointF mCoor; //����
	QPointF mSceneCoor; // ��scene�е�����
	int mId; //rowid
	int mNo; //���
	int mJunctionType; // ��������
	bool mInScale; // �Ƿ��ڷ�Χ��
	bool mHaveTurnRestrict;

};



inline uint qHash(Node n, uint seed = 0){
	return 0;
}


qreal length(QPair<Node,Node> pair);





#endif // !NODE
