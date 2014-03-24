#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include <QDialog>

#include <QSize>
#include <QList>

#include "legendelement.h"

/*
* ����ͼ�����ݵ�name type color����Ϣ, Legend��������Ӧ�����ͽ��л���
*/
class Legend : public QDialog
{
    Q_OBJECT
public:
    explicit Legend(QList<LegendElement> elements, QWidget *parent);
    Legend* setElements(QList<LegendElement> elelist);
	void draw();

signals:
	void posChange(QString);

public slots:
	void updatePos();

protected:
	void moveEvent(QMoveEvent * );
	void paintEvent(QPaintEvent *);

private:
	void initPos();

    QList<LegendElement> mElements;
	bool mFirstShow;
};

#endif // LEGEND_H
