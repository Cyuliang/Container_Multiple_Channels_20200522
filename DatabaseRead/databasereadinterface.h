#ifndef DATABASEREADINTERFACE_H
#define DATABASEREADINTERFACE_H

#define ZBY_LOG(type)  tr("[%1][%2][%3]").arg(type).arg(Q_FUNC_INFO).arg(__LINE__)

#include <QObject>
#include <QMap>
#include <QSqlTableModel>

class DatabaseReadInterface : public QObject
{
    Q_OBJECT

public:
    virtual ~ DatabaseReadInterface(){}

signals:

    ///
    /// \brief messageSignal 日志信息
    /// \param type 日志类型
    /// \param msg 信息体
    ///
    void messageSignal(const QString &type,const QString &msg);

    ///
    /// \brief returnModelSingal 返回数据模型
    /// \param model 数据模型
    ///
    void returnModelSingal( QSqlTableModel *model);

    ///
    /// \brief statisticalDataSignal
    /// \param total 总计
    /// \param correct 正确
    /// \param error 错误
    /// \param statistical 统计
    ///
    void statisticalDataSignal(int total,double correct,double error,double statistical);

public slots:

    ///
    /// \brief initDatabaseSlot 初始化数据库.如果不存在,就创建.
    /// \param connectName 链接名称
    /// \param user 用户名
    /// \param pass密码
    /// \param ip 地址
    ///
    virtual void initDatabaseSlot(const QString &connectName,const QString &user,const QString &pass,const QString &ip)=0;

    ///
    /// \brief setDatabaseFilterSlot 设置数据库筛选条件
    /// \param filter 筛选条件
    ///
    virtual void setDatabaseFilterSlot(const QString &filter)=0;
};

#define DatabaseReadInterfaceIID "ZBY.ContainerServer.DatabaseReadInterface/1.0"
Q_DECLARE_INTERFACE(DatabaseReadInterface,DatabaseReadInterfaceIID);

#endif // DATABASEREADINTERFACE_H
