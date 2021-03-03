﻿#include "datainterchange.h"
#include <QDebug>

DataInterchange::DataInterchange(QObject *parent)
{
    this->setParent(parent);

    isHeartBeat=false;
    isConnected=false;
    pTcpServer=nullptr;
    pTcpClient=nullptr;
    pTimerLinkState=nullptr;
}

DataInterchange::~DataInterchange()
{
    qDebug()<<"~DataInterchange";
}

QString DataInterchange::InterfaceType()
{
    return "DataInterchange";
}

void DataInterchange::InitializationParameterSlot(const QString& address, const quint16& port, const int& serviceType,const bool& heartBeat, const int& serviceMode,const int& shortLink)
{
    this->address=address;
    this->port=port;
    this->shortLink=shortLink;

    if(serviceMode==1){/* 服务器模式 */
        pTcpServer=new TcpServer (this);
        pTcpServer->setServiceType(serviceType);/* 设置服务模式 */
        /* 日志信息 */
        connect(pTcpServer,&TcpServer::messageSignal,this,&DataInterchange::messageSignal);
        /* 心跳包状态设置 */
        connect(this,&DataInterchange::setHeartbeatPackStateSignal,pTcpServer,&TcpServer::setHeartPacketStateSlot);
        /* 绑定客户端数量 */
        connect(pTcpServer,&TcpServer::connectCountSignal,this,&DataInterchange::connectCountSignal);
        /* 发送识别结果 */
        connect(this,&DataInterchange::toSendDataSignal,pTcpServer,&TcpServer::toSendDataSlot);                

        startListenSlot();
    }
    else if (serviceMode==0) {/* 客户端模式 */
        pTcpClient=new QTcpSocket(this);
        pTimerLinkState=new QTimer (this);

        /* 发送识别结果 */
        connect(this,&DataInterchange::toSendDataSignal,this,&DataInterchange::toSendDataSlot);
        /* 心跳包状态设置 */
        connect(this,&DataInterchange::setHeartbeatPackStateSignal,this,&DataInterchange::setHeartPacketStateSlot);

        connect(pTcpClient,&QIODevice::readyRead,this,&DataInterchange::receiveDataSlot);
        connect(pTcpClient,&QAbstractSocket::connected,this,&DataInterchange::connectedSlot);
        connect(pTcpClient,&QAbstractSocket::disconnected,this,&DataInterchange::disconnectedSlot);
        connect(pTcpClient,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&DataInterchange::displayErrorSlot);
        connect(pTimerLinkState,&QTimer::timeout,this,&DataInterchange::heartbeatSlot);

        /*****************************
        * @brief:不是短链接，服务器启动主动链接
        ******************************/
        if(!shortLink){
            startLinkSlot();
        }
    }
    emit setHeartbeatPackStateSignal(heartBeat);
}

void DataInterchange::startLinkSlot()
{
    if(!isConnected){
        pTcpClient->close();
        pTcpClient->abort();
        pTcpClient->connectToHost(address,port);
    }
}

void DataInterchange::startListenSlot()
{
    if(!pTcpServer->listen(QHostAddress::AnyIPv4,port)){/* 服务器使用本机地址 */
        qWarning().noquote()<<QString("IP:%1 Listen error<errocCode=%2>").arg(address).arg(pTcpServer->errorString());
    }
    else {
        qDebug().noquote()<<QString("IP:%1 Start listen.").arg(address);
    }
}

void DataInterchange::heartbeatSlot()
{
    if(isHeartBeat && pTcpClient->isOpen()){
        pTcpClient->write("[H]");/* 心跳包数据 */
    }
}

void DataInterchange::connectedSlot()
{
    isConnected=true;

    if(!pTimerLinkState->isActive()){
        pTimerLinkState->start(15000);
    }

    emit connectCountSignal(1);
    emit linkStateSingal(address,true);
    qDebug().noquote()<<QString("IP:%1:%2 link successful").arg(address).arg(port);
}

void DataInterchange::receiveDataSlot()
{
    /*****************************
    * @brief:服务器主动取结果
    ******************************/
    QByteArray buf=pTcpClient->readAll();    
    if(buf.trimmed().startsWith('[')){
        QList<QByteArray> tmp=buf.split('|');
        if(tmp.count()==2){
            if (tmp[0].indexOf('R')!=-1) {/* 找到取结果标志位 */
                pTcpClient->write(resultOfMemory.toLocal8Bit());
            }
        }
    }
    buf.clear();
}

void DataInterchange::disconnectedSlot()
{
    isConnected=false;
    emit connectCountSignal(-1);
    emit linkStateSingal(address,false);
}

void DataInterchange::displayErrorSlot(QAbstractSocket::SocketError socketError)
{
    isConnected=false;

    if(!shortLink){
        QTimer::singleShot(15000, this, SLOT(startLinkSlot()));
    }
    qWarning().noquote()<<QString("IP:%1:%3  link error<errorCode=%2>").arg(address).arg(socketError).arg(port);
}

void DataInterchange::setHeartPacketStateSlot(bool state)
{
    isHeartBeat=state;
}

void DataInterchange::toSendDataSlot(int channel_number,const QString &data)
{
    Q_UNUSED(channel_number);

    resultOfMemory=data;

    if(!pTcpClient->isOpen()){
        startLinkSlot();
        pTcpClient->waitForConnected(3000);
    }
    pTcpClient->write(data.toLocal8Bit());

    if(shortLink){
        /*****************************
        * @brief:发送完成主动断开
        ******************************/
        pTcpClient->waitForBytesWritten();
        pTcpClient->close();
        pTcpClient->abort();
    }
}

void DataInterchange::releaseResourcesSlot()
{
    isConnected=false;

    if(pTcpServer!=nullptr){
        pTcpServer->releaseResourcesSlot();
    }

    if(pTcpClient != nullptr){
         pTcpClient->abort();
    }

    if(pTcpServer!=nullptr){
         pTcpServer->close();
    }

    if(pTimerLinkState!=nullptr){
        pTimerLinkState->stop();
    }
}
