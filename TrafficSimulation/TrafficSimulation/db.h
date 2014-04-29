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
class RoadPermission;
class TrafficVolume;
class Speed;
class Capability;

class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = 0);
    ~DB();

    void createTablesAndFetchData();
    void setFileDir(QString dir);
    void clearTables(QSqlDatabase&);

	//  ------------------  new  --------------------
	QList<Node*> loadNodes();  // ��������node��
	QList<Edge*> loadEdges();  // ��������conn��
	QList<BusRoute*> loadBusRoutes(); // ��������bus��
	QList<TurnRestrict*> loadTurnRestrictions();
	QList<RoadPermission*> loadTrafficForbid(); // ��ֹͨ�б�����
	QList<RoadPermission*> loadTrafficNumLimit(); // �޺�ͨ�б�����
	QList<TrafficVolume*> loadNodeTrafficVolume();
	QList<TrafficVolume*> loadRoadTrafficVolume();
	QList<Capability*> loadNodeCapability();
	QList<Capability*> loadRoadCapability();
	QList<Speed*> loadSpeed();
	

	// set
	void setCreateDbName(QString);
	void setSelectedDbName(QString);

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
	void createNodeVolumeTable(QSqlQuery & query);
	void createRoadVolumeTable(QSqlQuery & query);
	void createNodeCapabilityTable(QSqlQuery & query);
	void createRoadCapabilityTable(QSqlQuery & query);
	void createSpeedTable(QSqlQuery & query);
	
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
	void fetchDataFromNodeVolumeFiles(QSqlQuery & query);
	void fetchDataFromRoadVolumeFiles(QSqlQuery & query);
	void fetchDataFromNodeCapabilityFile(QSqlQuery & query);
	void fetchDataFromRoadCapabilityFile(QSqlQuery & query);
	void fetchDataFromSpeedFile(QSqlQuery & query);

    //
    void insertForbidAndRestrict(QSqlQuery & , QString , QString );

private:
    QDir* mFileDir;
	QString mCreateDbName;
	QString mSelectedDbName;

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
	static const QString sNodeVolumeTableName;
	static const QString sRoadVolumeTableName;
	static const QString sNodeCapabilityTableName;
	static const QString sRoadCapabilityTableName;
	static const QString sSpeedTableName;

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

	///// ��ͨ���ļ�
	static const QString sNodeMotorVolumeFileName;
	static const QString sNodeNonMotorVolumeFileName;
	static const QString sNodeCarVolumeFileName;
	static const QString sNodeBusVolumeFileName;
	static const QString sNodeMotorbikeVolumeFileName;
	static const QString sNodeTruckVolumeFileName;
	static const QString sNodeTaxiVolumeFileName;
	static const QString sRoadMotorVolumeFileName;
	static const QString sRoadNonMotorVolumeFileName;
	static const QString sRoadCarVolumeFileName;
	static const QString sRoadBusVolumeFileName;
	static const QString sRoadMotorbikeVolumeFileName;
	static const QString sRoadTruckVolumeFileName;
	static const QString sRoadTaxiVolumeFileName;
	//// ��ͨ�������ļ�
	static const QString sNodeMotorCapabilityFileName;
	static const QString sNodeNonMotorCapabilityFileName;
	static const QString sRoadMotorCapabilityFileName;
	static const QString sRoadNonMotorCapabilityFileName;
	// �ٶ��ļ�
	static const QString sSpeedFileName;

    // �������sql���
    static const QString sSqlCreateNodeTable;
    static const QString sSqlCreateConnTable;
    static const QString sSqlCreateTrafficAreaTable;
    static const QString sSqlCreateTurnRestrictTable;
    static const QString sSqlCreateBusTable;
    static const QString sSqlCreateForbidConnTable;
    static const QString sSqlCreateRestrictConnTable;
	static const QString sSqlCreateNodeVolumeTable;
	static const QString sSqlCreateRoadVolumeTable;
	static const QString sSqlCreateNodeCapabilityTable;
	static const QString sSqlCreateRoadCapabilityTable;
	static const QString sSqlCreateSpeedTable;

};

#endif // DB_H
