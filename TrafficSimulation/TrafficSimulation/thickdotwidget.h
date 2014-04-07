#ifndef THICKDOTWIDGET_H
#define THICKDOTWIDGET_H

#include <QWidget>

class ThickDotWidget : public QWidget
{
	Q_OBJECT

public:
	ThickDotWidget(QWidget *parent = 0);
	
	ThickDotWidget(qreal radius, QColor inColor, QColor outColor, QWidget* parent=0);
	~ThickDotWidget();

protected:
	void paintEvent(QPaintEvent *);

private:
	QColor mInColor;
	QColor mOutColor;
	qreal mSize; // ��Ȧ�뾶, ��Ȧ�뾶С1
};

#endif // THICKDOTWIDGET_H
