#pragma once

#include "db.h"
#include "node.h"
#include "conn.h"

typedef NodeWithCoorNo Node;

class DbAdapter
{
public:
	DbAdapter(void);
	~DbAdapter(void);

	QList<QPair<Node,Node> >* loadNormConns();
	QList<ConnWithCoorLevel>* loadNormConnWithLevel();
	QHash<ConnWithCoorPair,int>* loadNormConnWithBusNum();
	QList<QPointF>* loadNodes();

private:
	void normConns(QList<QPair<Node,Node> > *);
	void normConns(QList<ConnWithCoorLevel>* );
	void normConns(QHash<ConnWithCoorPair,int>*);
	void norm(QList<QPointF>*) const;

private:
	DB* mDb;



};

