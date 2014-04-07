
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
	Node(){};
	Node(const Node & );
	Node & operator = (const Node & );
	Node(QPointF, int);
	bool operator==(const Node & node)const;

	Rect border() const;
	void norm(qreal, QPointF);

	// get
	QPointF coor() const;
	int no() const;
	QPointF sceneCoor() const;
	// set
	Node& setCoor(QPointF);
	Node& setNo(int);
	Node& setSceneCoor(QPointF);

private:
	QPointF mCoor; //����
	QPointF mSceneCoor; // ��scene�е�����
	int mNo; //���


};



inline uint qHash(Node n, uint seed = 0){
	return 0;
}


qreal length(QPair<Node,Node> pair);





#endif // !NODE
