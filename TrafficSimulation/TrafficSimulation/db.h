#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QVector>
#include <QPair>

#include "node.h"
#include "conn.h"

class Edge;
class BusRoute;
class TurnRestrict;

class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = 0);
    ~DB();

    QStringList createTablesAndFetchData();
    void setFileDir(QString dir);
    void clearTables();

	//  ------------------  new  --------------------
	QList<Node*> loadNodes();  // ��������node��
	QList<Edge*> loadEdges();  // ��������conn��
	QList<BusRoute*> loadBusRoutes(); // ��������bus��
	QList<TurnRestrict*> loadTurnRestrictions();

private:


signals:

public slots:

private:
    // �������ֱ�ĺ���, ������ʵ��ֻ��һ�仰
    void createNodeTable(QSqlQuery & query);
    void createConnTable(QSqlQuery & query);
    void createTrafficAreaTable(QSqlQuery & query);
    void createTurnRestrictTable(QSqlQuery & query);
    void createBusTable(QSqlQuery & query);
    void createForbidCoonTable(QSqlQuery & query);
    void createRestrictConnTable(QSqlQuery & query);
    // �������ļ��л�ȡ����Ȼ��浽���ݿ�
    void fetchDataFromConnFile(QSqlQuery & query); // ���ò��û��
    void fetchDataFromSectionFile(QSqlQuery & query);
    void fetchDataFromCoorFile(QSqlQuery & query);
    void fetchDataFromTrafficNode2OriNodeFile(QSqlQuery & query);
    void fetchDataFromTrafficNodeTypeFile(QSqlQuery & query);
    void fetchDataFromRestrictTurnFile(QSqlQuery & query);
    void fetchDataFromRoadTypeFile(QSqlQuery & query);
    void fetchDataFromForbiddenAreaFile(QSqlQuery & query);
    void fetchDataFromRestrictAreaFile(QSqlQuery & query);
    void fetchDataFromBusStopFile(QSqlQuery & query);
    void fetchDataFromBusNumFile(QSqlQuery & query);
    void fetchDataFromNodeStatisticsFile(QSqlQuery & query);
    void fetchDataFromRoadStatisticsFile(QSqlQuery & query);

    //
    void insertForbidAndRestrict(QSqlQuery & , QString , QString );

private:
    QSqlDatabase mDb;
    QString mConnName;
    QDir* mFileDir;

    // -------   static  area  ----------
    static const QString sDbType;
    static const QString sDbName;
    // ���ݿ�������
    static const QString sNodeTableName;
    static const QString sConnTableName;
    static const QString sTrafficAreaTableName;
    static const QString sTurnRestrictTableName;
    static const QString sBusTableName;
    static const QString sForbiddenConnTableName;
    static const QString sRestrictConnTableName;
    //�����ļ�����
    static const QString sConnFileName;
    static const QString sSectionFileName;
    static const QString sCoorFileName;
    static const QString sTrafficNode2OriNodeFileName;
    static const QString sTrafficNodeTypeFileName;
    static const QString sRestrictTurnFileName;
    static const QString sRoadTypeFileName;
    static const QString sForbiddenAreaFileName;
    static const QString sRestrictAreaFileName;
    static const QString sBusStopFileName;
    static const QString sBusNumFileName;
    static const QString sNodeStatisticsFileName;
    static const QString sRoadStatisticsFileName;
    // �������sql���
    static const QString sSqlCreateNodeTable;
    static const QString sSqlCreateConnTable;
    static const QString sSqlCreateTrafficAreaTable;
    static const QString sSqlCreateTurnRestrictTable;
    static const QString sSqlCreateBusTable;
    static const QString sSqlCreateForbidConnTable;
    static const QString sSqlCreateRestrictConnTable;

};

#endif // DB_H
