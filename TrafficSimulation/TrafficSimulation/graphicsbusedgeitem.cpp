#include "graphicsbusedgeitem.h"
#include "Edge.h"

GraphicsBusEdgeItem::GraphicsBusEdgeItem(QGraphicsItem *parent)
	: GraphicsEdgeItem(parent)
{

}

GraphicsBusEdgeItem::~GraphicsBusEdgeItem()
{

}

void GraphicsBusEdgeItem::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
	QString msg = QStringLiteral("·�α��: ") + QString::number(mEdgeData->sourceNode()->no())
		+ "-" + QString::number(mEdgeData->destNode()->no()) + ";  "
		+ QStringLiteral("��������Ŀ: ") + QString::number(mEdgeData->busNum());
	emit sendTmpInfoToStatus(msg);
}
