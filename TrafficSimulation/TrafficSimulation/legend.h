#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include <QDialog>

#include <QSize>
#include <QList>

#include "legendelement.h"

class QGridLayout;

/*
* ����ͼ�����ݵ�name type color����Ϣ, Legend��������Ӧ�����ͽ��л���
*/
class Legend : public QDialog
{
    Q_OBJECT
public:
    explicit Legend(QList<LegendElement> elements, QWidget *parent=0);
    Legend* setElements(QList<LegendElement> elelist);
	void draw();
	void updateAttr(QList<QColor>, QList<qreal>);
	void updateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList);

signals:
	void posChange(QString);

public slots:

protected:
	void paintEvent(QPaintEvent *);

private:
	QGridLayout* mLayout;
    QList<LegendElement> mElements;
	bool mFirstShow;
};

#endif // LEGEND_H
