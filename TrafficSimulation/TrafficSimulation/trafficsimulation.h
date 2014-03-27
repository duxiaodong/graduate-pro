#ifndef TRAFFICSIMULATION_H
#define TRAFFICSIMULATION_H

#include <QtWidgets/QMainWindow>
#include "ui_trafficsimulation.h"
#include "selectgraphicswidget.h"

/*
- ���Ƹ��ֽ�ͨͼ���л�
*/
class TrafficSimulation : public QMainWindow
{
	Q_OBJECT

public:
	TrafficSimulation(QWidget *parent = 0);
	~TrafficSimulation();

protected:
	void paintEvent(QPaintEvent *);

public slots:
	void showSelectGraphicsDialog();
	void changeGraphics(int,int);

private:
	void initActions();
	void initToolBar();

private:
	Ui::TrafficSimulationClass ui;
	// action
	QAction* mSelectGraphicsAction;
	QAction* mPrintAction;
	// 
	bool mNoGraphics;
	int mCurrentComIndex;
	int mCurrentListIndex;
	// toolbar
	QToolBar* mToolBar;
	// ѡ��ͨͼ�ĶԻ���
	SelectGraphicsWidget* mSelectGraphicsDialog;
	// ����ͼ
};

#endif // TRAFFICSIMULATION_H
