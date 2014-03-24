#ifndef CONN_H
#define CONN_H

#include <QtCore>

struct ConnWithCoorLevel
{
	QPair<QPointF,QPointF> mCoorPair;
	int mRoadLevel;

	ConnWithCoorLevel(){};
	ConnWithCoorLevel(QPair<QPointF,QPointF> coor, int level);
	void setConn(QPair<QPointF,QPointF> coor);
	void setLevel(int level);
};

struct ConnWithNoPair
{
	int node1;
	int node2;

	ConnWithNoPair(){}
	ConnWithNoPair(int,int);
	ConnWithNoPair(const ConnWithNoPair & conn);
	ConnWithNoPair& operator=(const ConnWithNoPair & conn);
	bool operator==(const ConnWithNoPair &) const;
};

inline uint qHash(const ConnWithNoPair & p, uint seed = 0){
	return 0 ;
}

QDataStream& operator<<(QDataStream& out, const ConnWithNoPair& conn);
QDataStream& operator>>(QDataStream& in, const ConnWithNoPair& conn);

struct ConnWithCoorPair
{
	QPair<QPointF,QPointF> mCoorPair;

	ConnWithCoorPair(){};
	ConnWithCoorPair(QPointF p1,QPointF p2);
	bool operator==(const ConnWithCoorPair &) const;
};

inline uint qHash(const ConnWithCoorPair & p, uint seed=0 ){
	return 0;
}


#endif // !CONN_H

