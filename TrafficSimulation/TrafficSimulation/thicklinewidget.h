#ifndef THICKLINEWIDGET_H
#define THICKLINEWIDGET_H

#include <QWidget>

class ThickLineWidget : public QWidget
{
	Q_OBJECT

public:
	ThickLineWidget(QWidget *parent = 0);
	ThickLineWidget(double width, QColor color, QColor outColor, bool have=true, QWidget* parent=0);
	~ThickLineWidget();

public slots:
	void changeInnerColor(QColor);
	void changeBorderColor(QColor);
	void changeSize(qreal);
	void changeHaveBorder(int);

protected:
	void paintEvent(QPaintEvent * event);

private:
	QColor mColor;
	QColor mOutColor;
	double mWidth; // ����߿�, �ڲ�-2
	bool mHaveBorder;

};

#endif // THICKLINEWIDGET_H
