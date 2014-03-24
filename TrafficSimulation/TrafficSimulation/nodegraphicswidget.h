#ifndef NODEGRAPHICSWIDGET_H
#define NODEGRAPHICSWIDGET_H

#include <QWidget>
#include "DbAdapter.h"
#include "node.h"
#include "graphicswidget.h"

class NodeGraphicsWidget : public GraphicsWidget
{
	Q_OBJECT

public:
	NodeGraphicsWidget(QWidget *parent = 0);
	~NodeGraphicsWidget();

protected:
	void paintGraphics(QPainter& , QPaintEvent *);
	void createLegend();

private:
	void extractNodes();
	void init(); // ��ʼ�����ֲ���

private:
	DbAdapter mDbAdapter;

	QList<QPair<Node,Node> >* mConnList; // ����·��
	QHash<Node,qreal>* mNodes;

	qreal mNodeRadius, mLineWidth;
	QColor mNodePenColor, mNodeBrushColor, mLineColor,mOutLineColor;

};

#endif // NODEGRAPHICSWIDGET_H
