#include "trafficsimulation.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// ���²��ֽ����������   
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));    
	// ���ϲ��ֽ����������

	TrafficSimulation w;
	w.show();
	return a.exec();
}
