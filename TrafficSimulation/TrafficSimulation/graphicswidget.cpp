#include "graphicswidget.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPrinter>


GraphicsWidget::GraphicsWidget(QWidget *parent)
	: QWidget(parent)
	, mPressed(false)
	, mOffset(QPoint(0,0))
	, mRatio(1.0)
	, mLegend(0)
	, mLegendShown(false)
	, mBackColor(QColor(242,239,232))
{
	connect(this, SIGNAL(paintCompleted()), this, SLOT(showLegend()));
	this->setCursor(Qt::CrossCursor);
	
}

GraphicsWidget::~GraphicsWidget()
{
	if(mLegend)
		delete mLegend;
}

QPointF GraphicsWidget::normCoorToScreenCoor( QPointF coor )
{
	QRect rect = this->rect();
	QPoint center = rect.center();
	int w = this->width();
	int h = this->height();
	int minL = w>h ? h:w;
	int x = center.x() + (coor.x()+mOffset.x())*minL*mRatio;
	int y = center.y() - (coor.y()+mOffset.y())*minL*mRatio;
	return QPoint(x,y);
}

void GraphicsWidget::mousePressEvent( QMouseEvent * event )
{
	mPressed = true;
	mPressCoor = event->pos();
	this->setCursor(Qt::PointingHandCursor);
}

void GraphicsWidget::mouseReleaseEvent( QMouseEvent * )
{
	mPressed = false;
	this->setCursor(Qt::CrossCursor);
}

void GraphicsWidget::mouseMoveEvent( QMouseEvent * event )
{
	if (mPressed)
	{
		QPoint currCoor = event->pos();
		QPoint delta = currCoor - mPressCoor;
		mPressCoor = currCoor;
		int w = this->width();
		int h = this->height();
		int minL = w>h ? h:w;
		mOffset += QPointF(delta.rx()/(qreal)(minL*mRatio),-delta.ry()/(qreal)(minL*mRatio)); // ע��y��ת��

		repaint();
	}
}

void GraphicsWidget::wheelEvent( QWheelEvent * event )
{
	// �õ�������ڵ����Ļ����͹�һ������
	// ��Ҫ����mRatio����֮ǰ
	QPoint pos = event->pos();
	QRect rect = this->rect();
	QPoint center = rect.center();
	int w = this->width();
	int h = this->height();
	int minL = w>h ? h:w;
	QPointF normCoor = QPointF((pos.x()-center.x())/(qreal)(minL*mRatio),
		(center.y()-pos.y())/(qreal)(minL*mRatio)) - mOffset; // ע��y�ı任

	// ���������
	QPoint numDegree = event->angleDelta()/8;
	QPoint numSteps = numDegree/15;
	mRatio -= 0.1 * numSteps.y();
	if(mRatio<1.0)
		mRatio = 1.0;

	// ����ƫ����
	QPointF tmpCoor = normCoor*mRatio*minL;
	QPointF coor = center + QPointF(tmpCoor.x(),-tmpCoor.y());
	QPointF delta = pos - coor;
	mOffset = QPointF(delta.x(),-delta.y())/(qreal)(minL*mRatio);

	repaint();
}

void GraphicsWidget::showLegend()
{
	if (!mLegendShown)
	{
		createLegend();
		mLegendShown = true;
	}
	
}

qreal GraphicsWidget::getRatio()
{
	return mRatio;
}

void GraphicsWidget::paintEvent( QPaintEvent * event )
{
	QPainter mPainter(this);
	mPainter.setRenderHint(QPainter::Antialiasing);
	mPainter.fillRect(this->rect(),mBackColor); // �������
	// ����ͼ
	mPainter.save();
	paintGraphics(mPainter,event);
	mPainter.restore();
	// ��Ȩ����
	mPainter.save();
	QFont font; font.setPointSize(13);
	mPainter.setFont(font);
	QRect rect = event->rect();
	QRect textRect(rect.left(),rect.bottom()-50,rect.width(),50);
	mPainter.drawText(textRect, Qt::AlignCenter, "copyright@ wang wei. SEU. NANJING");
	mPainter.restore();
	// ��������ź�
	emit paintCompleted();
}

void GraphicsWidget::printGraphics()
{
	QPainter painter;
	QPrinter printer;
	//printer.setOutputFileName("graphics.pdf");
	//printer.setOutputFormat(QPrinter::PdfFormat);
	painter.begin(&printer);

	double xscale = printer.pageRect().width()/double(this->width());
	double yscale = printer.pageRect().height()/double(this->height());
	double scale = qMin(xscale, yscale);
	painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
		printer.paperRect().y() + printer.pageRect().height()/2);
	painter.scale(scale, scale);
	painter.translate(-width()/2, -height()/2);

	this->render(&painter);

	painter.end();
}


