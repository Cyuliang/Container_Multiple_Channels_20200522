#include "thelicenseplatewty.h"

TheLicensePlateWTY *TheLicensePlateWTY::pThis=nullptr;

TheLicensePlateWTY::TheLicensePlateWTY(QObject *parent)
{
    this->setParent(parent);

    TheLicensePlateWTY::pThis=this;

    pDLL=nullptr;
    isSDKinit=false;
    address="";
    port=0;
    channel=0;
    imgPath="";
    arrAddr="";

    CLIENT_LPRC_RegCLIENTConnEvent=nullptr;
    CLIENT_LPRC_RegDataEx2Event=nullptr;
    CLIENT_LPRC_RegJpegEvent=nullptr;
    CLIENT_LPRC_RegWTYGetGpioState=nullptr;
    CLIENT_LPRC_RegSerialDataEvent=nullptr;
    CLIENT_LPRC_InitSDK=nullptr;
    CLIENT_LPRC_SetSavePath=nullptr;
    CLIENT_LPRC_SetTrigger=nullptr;
    CLIENT_LPRC_SetJpegStreamPlayOrStop=nullptr;
    CLIENT_LPRC_SetRelayClose=nullptr;
    CLIENT_LPRC_DropRod=nullptr;
    CLIENT_LPRC_SetNetworkCardBind=nullptr;
    CLIENT_LPRC_RS485Send=nullptr;
    CLIENT_LPRC_QuitDevice=nullptr;
}

TheLicensePlateWTY::~TheLicensePlateWTY()
{
    TheLicensePlateWTY::pThis=nullptr;

    if(pDLL!=nullptr  && pDLL->isLoaded()){
        pDLL->unload();
        delete pDLL;
        pDLL=nullptr;
    }
}

bool TheLicensePlateWTY::initializationParameter()
{
#ifdef Q_OS_LIUNX
    pDLL=new QLibrary (QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/WTY/linux/libwty")),this) ;/* linux */
#endif
#ifdef Q_OS_WIN
    pDLL=new QLibrary (QDir::toNativeSeparators(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("Plugins/WTY/windows/WTY")),this) ;/* windows*/
#endif

    if(pDLL->load()){
        CLIENT_LPRC_RegCLIENTConnEvent=reinterpret_cast<CLIENT_LPRC_RegCLIENTConnEventFUN>(pDLL->resolve("CLIENT_LPRC_RegCLIENTConnEvent"));
        CLIENT_LPRC_RegDataEx2Event=reinterpret_cast<CLIENT_LPRC_RegDataEx2EventFUN>(pDLL->resolve("CLIENT_LPRC_RegDataEx2Event"));
        CLIENT_LPRC_RegJpegEvent=reinterpret_cast<CLIENT_LPRC_RegJpegEventFUN>(pDLL->resolve("CLIENT_LPRC_RegJpegEvent"));
        CLIENT_LPRC_RegWTYGetGpioState=reinterpret_cast<CLIENT_LPRC_RegWTYGetGpioStateFUN>(pDLL->resolve("CLIENT_LPRC_RegWTYGetGpioState"));
        CLIENT_LPRC_RegSerialDataEvent=reinterpret_cast<CLIENT_LPRC_RegSerialDataEventFUN>(pDLL->resolve("CLIENT_LPRC_RegSerialDataEvent"));
        CLIENT_LPRC_InitSDK=reinterpret_cast<CLIENT_LPRC_InitSDKFUN>(pDLL->resolve("CLIENT_LPRC_InitSDK"));
        CLIENT_LPRC_SetSavePath=reinterpret_cast<CLIENT_LPRC_SetSavePathFUN>(pDLL->resolve("CLIENT_LPRC_SetSavePath"));
        CLIENT_LPRC_SetTrigger=reinterpret_cast<CLIENT_LPRC_SetTriggerFUN>(pDLL->resolve("CLIENT_LPRC_SetTrigger"));
        CLIENT_LPRC_SetJpegStreamPlayOrStop=reinterpret_cast<CLIENT_LPRC_SetJpegStreamPlayOrStopFUN>(pDLL->resolve("CLIENT_LPRC_SetJpegStreamPlayOrStop"));
        CLIENT_LPRC_SetRelayClose=reinterpret_cast<CLIENT_LPRC_SetRelayCloseFUN>(pDLL->resolve("CLIENT_LPRC_SetRelayClose"));
        CLIENT_LPRC_DropRod=reinterpret_cast<CLIENT_LPRC_DropRodFUN>(pDLL->resolve("CLIENT_LPRC_DropRod"));
        CLIENT_LPRC_SetNetworkCardBind=reinterpret_cast<CLIENT_LPRC_SetNetworkCardBindFUN>(pDLL->resolve("CLIENT_LPRC_SetNetworkCardBind"));
        CLIENT_LPRC_RS485Send=reinterpret_cast<CLIENT_LPRC_RS485SendFUN>(pDLL->resolve("CLIENT_LPRC_RS485Send"));
        CLIENT_LPRC_QuitDevice=reinterpret_cast<CLIENT_LPRC_QuitDeviceFUN>(pDLL->resolve("CLIENT_LPRC_QuitDevice"));

        return true;
    }

    qWarning()<<tr("Load the license plate dynamic library error<errorCode=%1>").arg(pDLL->errorString());
    delete pDLL;
    pDLL=nullptr;

    return  false;
}

void TheLicensePlateWTY::saveImg(QByteArray arrImg, const QString &time)
{
    QMutexLocker locket(&mutex);
    if(imgPath!=""){/* 保存路径不存在,图片不保存,不识别 */
        QString suffixPath="";
        switch (imgFormat) {
        case 0:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 1:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 2:
            suffixPath=QDir::toNativeSeparators(tr("%1/%2").arg(channel).arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 3:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(channel));
            break;
        case 4:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM/dd")));
            break;
        case 5:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy/MM")));
            break;
        case 6:
            suffixPath=QDir::toNativeSeparators(tr("%1").arg(QDateTime::currentDateTime().toString("yyyy")));
            break;
        case 7:
            suffixPath=QDir::toNativeSeparators("./");
            break;
        }

        QDir dir(imgPath);
        dir.mkpath(suffixPath);
        dir.cd(suffixPath);

        QPixmap *labelPix = new QPixmap();
        labelPix->loadFromData(arrImg);
        QPixmap labelPixFit=  labelPix->scaled(1280,720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);/* 缩放图片 */
        QString image=QDir::toNativeSeparators(tr("%1/%2%3%4.jpg").arg(dir.path()).arg(QDateTime::fromString(time,"yyyy-M-d h:m:s").toString("yyyyMMddhhmmss")).arg(7).arg(channel));
        labelPixFit.save(image);
        delete labelPix;
        labelPix=nullptr;
    }
}

void TheLicensePlateWTY::initCameraSlot(const QString  &localAddr,const QString &addr,const int &port,const QString &imgPath, int imgFormat,const int &channel)
{
    if(!isSDKinit){
        if(!initializationParameter()){
            return;
        }
        this->address=addr;
        this->port=port;
        this->imgPath=imgPath;
        this->channel=channel;
        this->imgFormat=imgFormat;

        CLIENT_LPRC_RegCLIENTConnEvent(TheLicensePlateWTY::connectCallback);
        CLIENT_LPRC_RegDataEx2Event(TheLicensePlateWTY::dataEx2Callback);
        CLIENT_LPRC_RegJpegEvent(TheLicensePlateWTY::jpegCallback);
        CLIENT_LPRC_RegWTYGetGpioState(TheLicensePlateWTY::getGpioStateCallback);
        CLIENT_LPRC_RegSerialDataEvent(TheLicensePlateWTY::serialDataCallback);

        QByteArray arr=imgPath.toLatin1();
        CLIENT_LPRC_SetSavePath(arr.data());

        arrAddr=localAddr.toLatin1();
        if(CLIENT_LPRC_SetNetworkCardBind(arrAddr.data())==0){
            qInfo()<<tr("IP:%1 Bind network card successfully %2").arg(address).arg(localAddr);
        }
        else {
            qWarning()<<tr("Failed to bind network card");
        }

        isSDKinit=true;
        arrAddr=addr.toLatin1();
        if(CLIENT_LPRC_InitSDK(static_cast<uint>(port),nullptr,0,arrAddr.data(),0)==0){
            qInfo()<<tr("IP:%1 License plate camera link successful").arg(addr);
        }
        else {
            qWarning()<<tr("IP:%1 License plate camera link faild").arg(addr);
        }
    }
}

void TheLicensePlateWTY::connectCallback(char *chWTYIP, UINT nStatus, LDWORD dwUser)
{
    Q_UNUSED(chWTYIP);
    Q_UNUSED(dwUser);

    bool state=false;
    if(nStatus==1){
        state=true;
    }
    emit pThis->equipmentStateSignal(state);
}

void TheLicensePlateWTY::dataEx2Callback(CLIENT_LPRC_PLATE_RESULTEX *recResultEx, LDWORD dwUser)
{
    Q_UNUSED(dwUser);

    QByteArray arrImg=QByteArray::fromRawData(reinterpret_cast<const char*>(recResultEx->pFullImage.pBuffer),recResultEx->pFullImage.nLen);

    /* 车牌相机时间，部分出现异常 */
    //QString dateTime= QString("%1-%2-%3 %4:%5:%6").arg(recResultEx->shootTime.Year).arg(recResultEx->shootTime.Month).arg(recResultEx->shootTime.Day).arg(recResultEx->shootTime.Hour).arg(recResultEx->shootTime.Minute).arg(recResultEx->shootTime.Second);

    /* 系统时间 */
    QString dateTime=QDateTime::currentDateTime().toString("yyyy-M-d h:m:s");

    emit pThis->resultsTheLicensePlateSignal(recResultEx->chLicense,recResultEx->chColor,dateTime,arrImg);
    qInfo()<<tr("License Plate recognition results:%1-%2").arg(QString::fromLocal8Bit(recResultEx->chLicense)).arg(dateTime);

    pThis->saveImg(arrImg,dateTime);
}

void TheLicensePlateWTY::jpegCallback(CLIENT_LPRC_DEVDATA_INFO *JpegInfo, LDWORD dwUser)
{
    Q_UNUSED(dwUser);

    if(JpegInfo->chIp==pThis->arrAddr.data() && JpegInfo->nStatus==0){
        QByteArray arrImg=QByteArray::fromRawData(reinterpret_cast<const char*>(JpegInfo->pchBuf),JpegInfo->nLen);
        emit pThis->theVideoStreamSignal(arrImg);
    }
}

void TheLicensePlateWTY::getGpioStateCallback(char *chWTYIP, CLIENT_LPRC_GPIO_In_Statue *pGpioState)
{
     /*
      * unsigned  char gpio_in0;      //GPIO IN0 0低电平 1 高电平
      * unsigned  char gpio_in1;     //GPIO IN1 0低电平 1 高电平
      * unsigned  char gpio_in2;     //GPIO IN2 0低电平 1 高电平
      * unsigned  char gpio_in3;     //GPIO IN3 0低电平 1 高电平
      */
    Q_UNUSED(chWTYIP);
    Q_UNUSED(pGpioState);
}

void TheLicensePlateWTY::serialDataCallback(char *chCLIENTIP, CLIENT_LPRC_DEVSERIAL_DATA *pSerialData, LDWORD dwUser)
{
    /*
     * unsigned char *pData;     // 串口数据指针
     * int nsize;                         // 串口数据大小
     * char reserved[128];          // 保留
     */
    Q_UNUSED(dwUser);
    Q_UNUSED(chCLIENTIP);
    Q_UNUSED(pSerialData);
}

void TheLicensePlateWTY::simulationCaptureSlot()
{
    if(CLIENT_LPRC_SetTrigger!=nullptr && CLIENT_LPRC_SetTrigger(arrAddr.data(),port)==0){
        qInfo()<<tr("IP:%1 The simulated snapshot was successful").arg(address);
    }
    else {
        qWarning()<<tr("IP:%1 Simulation capture failed").arg(address);
    }
}

void TheLicensePlateWTY::liftingElectronicRailingSlot(bool gate)
{
    if(gate){
        CLIENT_LPRC_SetRelayClose(arrAddr.data(),9110);
    }
    else {
        CLIENT_LPRC_DropRod(arrAddr.data(),9110);
    }
}

void TheLicensePlateWTY::transparentTransmission485Slot(const QString &msg)
{
    QByteArray arrMsg=msg.toLatin1();
    if(CLIENT_LPRC_RS485Send!=nullptr && CLIENT_LPRC_RS485Send(arrAddr.data(),9110,arrMsg.data(),arrMsg.length())==0){
        qInfo()<<tr("IP:%1 485 data forwarding was successful").arg(address);
    }
    else {
        qWarning()<<tr("IP:%1 485 data forwarding was failed").arg(address);
    }
}

void TheLicensePlateWTY::openTheVideoSlot(bool play)
{
    int mark=0;
    if(play){
        mark=1;
    }
    if(CLIENT_LPRC_SetJpegStreamPlayOrStop!=nullptr && CLIENT_LPRC_SetJpegStreamPlayOrStop(arrAddr.data(),mark)==0){
        qInfo()<<tr("IP:%1 Video streaming operation successful").arg(address);
    }
    else {
        qWarning()<<tr("IP:%1 Video streaming operation successful").arg(address);
    }
}

void TheLicensePlateWTY::releaseResourcesSlot()
{
    if(CLIENT_LPRC_QuitDevice!=nullptr){
        CLIENT_LPRC_QuitDevice(arrAddr.data());
    }
}