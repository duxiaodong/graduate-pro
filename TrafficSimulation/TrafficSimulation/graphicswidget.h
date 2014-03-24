#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "legend.h"
#include <QPainter>

/*
- ��ͼ���ƶ��ͷ���
- ������״����
- ��һ��������ת������Ļ���꣨������ƽ�ơ������ȱ任��
- ������ɺ�����ʾͼ��������ͼ����λ�ÿ��Ʋ��ˣ�
*/
class GraphicsWidget : public QWidget
{
	Q_OBJECT

public:
	GraphicsWidget(QWidget *parent = 0);
	~GraphicsWidget();

signals:
	void paintCompleted();

public slots:
	void showLegend();
	void printGraphics();


protected:
	QPointF normCoorToScreenCoor( QPointF coor );
	virtual void createLegend() = 0; //�����˴�����show
	virtual void paintGraphics(QPainter& p, QPaintEvent* event) = 0;
	// �¼�
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *);
	// ��������paintEventʱ��Ȼ��Ҫ���ô˺���
	// ����ʵ�ֹ��еĹ���: - ����ɫ���  - ��Ȩ����  - �����������ź�
	void paintEvent(QPaintEvent *);
	// ��ȡ���ű���
	qreal getRatio();


protected:
	Legend* mLegend;
	QColor mBackColor;

private:
	// �����϶��ı���
	bool mPressed; // �Ƿ�������������״̬
	QPointF mOffset; // ͼ��λ��
	QPoint mPressCoor; // �������λ��
	// ��������ı���
	qreal mRatio;
	// ͼ���Ի���
	bool mLegendShown;

	

};

#endif // GRAPHICSWIDGET_H
