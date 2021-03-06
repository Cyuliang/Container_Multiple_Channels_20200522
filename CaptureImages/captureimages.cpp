﻿#include "captureimages.h"

CaptureImages::CaptureImages(QObject *parent)
{
    this->setParent(parent);

    signature="";
    imgNumber=-1;
    camerID=-1;
    put=false;
    imgGetTimeOut=new QTimer(this);
    imgGetTimeOut->setSingleShot(true);
    connect(imgGetTimeOut,SIGNAL(timeout()),this,SLOT(slot_imgGetTimeOut()));
}

CaptureImages::~CaptureImages()
{
}

bool CaptureImages::InitializationSlot()
{
    return false;
}

void CaptureImages::initCamerSlot(const QString &localAddr,const QString &camerIP, const int &camerPort,const QString &CamerUser,const QString &CamerPow,const QString &signature)
{
    this->signature=signature;
    this->camerIP=camerIP;

    if(camerIP.isEmpty() || camerIP=="..."){
        return;
    }   
    emit signal_initCamera(localAddr,camerIP,camerPort,CamerUser,CamerPow);
}

void CaptureImages::getDeviceStatusSlot()
{   
}

void CaptureImages::slot_imgGetTimeOut()
{
    put=false;
    emit pictureStreamSignal(nullptr,imgNumber,imgTime);
}

bool CaptureImages::putCommandSlot( int imgNumber, QString imgTime,const QString &signature)
{    
    if(this->signature.isEmpty() || this->signature==signature){
        if(camerID==-1){
            emit pictureStreamSignal(nullptr,imgNumber,imgTime);
            qWarning().noquote()<<signature<<":Camera not logged in, return null";
            return false;
        }
        if(imgGetTimeOut->isActive()){
            emit pictureStreamSignal(nullptr,this->imgNumber,this->imgTime);
            qWarning().noquote()<<signature<<":The camera result returns a timeout and a null value";
            imgGetTimeOut->stop();
        }

        qDebug().noquote()<<"Capture the image:"<<camerID;

        put=true;
        this->imgNumber=imgNumber;
        this->imgTime=imgTime;
        emit signal_simulationCapture(camerID);
        imgGetTimeOut->start(3000);
        return true;
    }
    //qDebug().noquote()<<signature<<":Camera not logged in";
    return false;
}

void CaptureImages::playStreamSlot(quint64 winID,bool play,const QString &signature)
{
    if(this->signature.isEmpty() || this->signature==signature){
        emit signal_openTheVideo(camerID,play,winID);
        qInfo().noquote()<<signature<<":The camera preview";
    }
}

void CaptureImages::liftingElectronicRailingSlot(bool gate)
{
    Q_UNUSED(gate);
}

void CaptureImages::transparentTransmission485Slot(const QString &msg)
{
    Q_UNUSED(msg);
}

void CaptureImages::resizeEventSlot()
{
}

void CaptureImages::releaseResourcesSlot()
{
    imgGetTimeOut->stop();

    qDebug().noquote()<<"CaptureImages::releaseResourcesSlot";
}

void CaptureImages::slot_pictureStream(int ID, QByteArray arrJpg)
{
    if(put && ID==camerID){
        emit pictureStreamSignal(arrJpg,imgNumber,imgTime);
        qDebug().noquote()<<QString("IP=%1[%2]:%3").arg(camerIP,signature,":Put Command Sucess");
        put=false;
        imgGetTimeOut->stop();

        if(nullptr==arrJpg){
            qWarning().noquote()<<signature<<":Capture image data is empty";
        }
    }
}

void CaptureImages::slot_setCameraID(int ID, QString cameraIP)
{
    if(camerIP==cameraIP && -1==camerID){
        camerID=ID;
        qDebug()<<QString("IP=%1 Set the ID[%2]").arg(cameraIP).arg(ID);
    }
}

void CaptureImages::slot_resultsTheLicensePlate(int ID, const QString &plate, const QString &color, const QString &time,const QByteArray &arrImg)
{
    /*****************************
    * @brief:集装箱不接受车牌信息
    ******************************/
    Q_UNUSED(ID);
    Q_UNUSED(plate);
    Q_UNUSED(color);
    Q_UNUSED(time);
    Q_UNUSED(arrImg);
}

void CaptureImages::slot_equipmentState(int ID, bool state)
{
    if(camerID==ID){
        emit camerStateSingal(camerIP,state);
        if(!state){
            camerID=-1;
        }
    }
}
