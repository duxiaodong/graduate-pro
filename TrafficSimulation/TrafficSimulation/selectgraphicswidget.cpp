#include "selectgraphicswidget.h"

SelectGraphicsWidget::SelectGraphicsWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	init();
	connect(ui.comboBox,SIGNAL(currentIndexChanged(int)),
		this, SLOT(comboBoxIndexChanged(int)));
	connect(ui.cancelButton, SIGNAL(clicked()),this,SLOT(close()));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(ok()));

	ui.listWidget->insertItems(0,mList0);

	this->setModal(true);
	
}

SelectGraphicsWidget::~SelectGraphicsWidget()
{

}

void SelectGraphicsWidget::comboBoxIndexChanged( int index )
{
	while (ui.listWidget->count()>0)
	{
		ui.listWidget->takeItem(0);
	}
	switch (index)
	{
	case 0:
		{
			ui.listWidget->insertItems(0,mList0);
			break;
		}
	case 1:
		{
			ui.listWidget->insertItems(0,mList1);
			break;
		}
	case 2:
		{
			ui.listWidget->insertItems(0,mList2);
			break;
		}
	case 3:
		{
			ui.listWidget->insertItems(0,mList3);
			break;
		}
	default:
		break;
	}
}

void SelectGraphicsWidget::init()
{
	mList0<<QStringLiteral("1.道路网络等级分布")
		<<QStringLiteral("2.道路网络节点编号")
		<<QStringLiteral("3.公共交通线网分布");
	mList1<<QStringLiteral("1.交叉口类型分布")<<QStringLiteral("2.转向限制交叉口分布")
		<<QStringLiteral("3.道路类型管理信息")<<QStringLiteral("4.道路交通管理信息")
		<<QStringLiteral("5.自行车禁止通行区域分布")<<QStringLiteral("6.客车禁止通行区域分布")
		<<QStringLiteral("7.摩托车禁止通行区域分布")<<QStringLiteral("8.出租车禁止通行区域分布")
		<<QStringLiteral("9.公共汽车禁止通行区域分布")<<QStringLiteral("10.货车禁止通行区域分布")
		<<QStringLiteral("11.客车限号通行区域分布")<<QStringLiteral("12.摩托车限号通行区域分布")
		<<QStringLiteral("13.出租车限号通行区域分布")<<QStringLiteral("14.货车限号通行区域分布");
	mList2<<QStringLiteral("1.机动车路段交通量分布")<<QStringLiteral("2.机动车交叉路口交通量分布")
		<<QStringLiteral("3.非机动车路段交通量分布")<<QStringLiteral("4.非机动车交叉口交通量分布")
		<<QStringLiteral("5.客车路段交通量分布")<<QStringLiteral("6.公交车路段交通量分布")
		<<QStringLiteral("7.摩托车路段交通量分布")<<QStringLiteral("8.货车路段交通量分布")
		<<QStringLiteral("9.出租车路段交通量分布")<<QStringLiteral("10.客车交叉口交通量分布")
		<<QStringLiteral("11.公交车交叉口交通量分布")<<QStringLiteral("12.摩托车交叉口交通量分布")
		<<QStringLiteral("13.货车交叉口交通量分布")<<QStringLiteral("14.出租车交叉口交通量分布");
	mList3<<QStringLiteral("1.机动车路段交通负荷分布")<<QStringLiteral("2.机动车交叉口交通负荷分布")
		<<QStringLiteral("3.非机动车路段交通负荷分布")<<QStringLiteral("4.非机动车交叉口负荷分布")
		<<QStringLiteral("5.机动车路段平均车速分布");

}



void SelectGraphicsWidget::ok()
{
	int comboBoxIndex = ui.comboBox->currentIndex();
	QListWidgetItem* currentItem = ui.listWidget->currentItem();
	if (!currentItem)
	{
		QMessageBox::critical(this,QStringLiteral("请选择交通图"),QStringLiteral("您尚未选择交通图"));
		return ;
	}
	
	QStringList tmpList;
	switch (comboBoxIndex)
	{
	case 0:
		{
			tmpList = mList0;
			break;
		}
	case 1:
		{
			tmpList = mList1;
			break;
		}
	case 2:
		{
			tmpList = mList2;
			break;
		}
	case 3:
		{
			tmpList = mList3;
			break;
		}
	default:
		break;
	}
	int listIndex = indexInList(currentItem->text(),tmpList);
	close();
	emit selectGraphics(comboBoxIndex,listIndex);
	
}

int SelectGraphicsWidget::indexInList( QString str, QStringList sl )
{
	for (int i=0;i<sl.size();++i)
	{
		if(str == sl.at(i))
			return i;
	}

}
