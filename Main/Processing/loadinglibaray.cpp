﻿#include "loadinglibaray.h"

LoadingLibaray::LoadingLibaray(int ChannelNumber, QObject *parent) : QObject(parent)
{
    channelCount=ChannelNumber;
}

void LoadingLibaray::slot_destructorThread()
{
    foreach (auto thread, tdList) {
        thread->quit();
        thread->wait();
    }
    loadVec.clear();
    qDebug().noquote()<<QString("~LoadingLibaray");
}

void LoadingLibaray::loadMisarrangement(QString pluginName,QString interType)
{
    if(-1!=loadVec.indexOf(interType)){
        emit signal_loadPluginError(pluginName);/* 加载相同插件多次报错 */
    }
    else {
        loadVec.append(interType);
    }
}

void LoadingLibaray::slot_createLibaray()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());

    /*  创建插件目录  */
    const QString pluginPath="Plugins";
    pluginsDir.mkdir(pluginPath);
    pluginsDir.cd(pluginPath);

    const QString path=pluginsDir.path();

    /*****************************
    * @brief: 插件数量
    ******************************/
    int pluginsNum=0;

    /*****************************
    * @brief:删除非插件类文件夹
    ******************************/
    for(const QString fileName :pluginsDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)){
        if("HCNetSDK"!=fileName && "OLD"!=fileName){
            QDir dir(QDir::toNativeSeparators(path+"/"+fileName));
            dir.removeRecursively();
        }
    }

    for(const QString fileName :pluginsDir.entryList(QDir::Files,QDir::Name)){
        QPluginLoader  pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if(plugin){
            const QString pluginName=fileName.split(".").at(0);
            /*  创建子插件目录 */
            pluginsDir.mkdir(pluginName);
            pluginsDir.cd(pluginName);
            /*  删除旧插件   */
            for(QFileInfo file :pluginsDir.entryInfoList()){
                if(file.isFile()){
                    file.dir().remove(file.fileName());
                }
            }

            /*****************************
            * @brief: 插件数量
            ******************************/
            pluginsNum=0;

            if(ICaptureImages *pICaptureImages=qobject_cast<ICaptureImages*>(plugin)){
                pluginsNum=channelCount*LocalPar::CamerNumber;
                loadMisarrangement(pluginName,"ICaptureImages");
                pICaptureImages=nullptr;
            }
            else if(IMiddleware *pIMiddleware=qobject_cast<IMiddleware*>(plugin)) {
                if(0==Parameter::Camera_Load_Plugin){
                    pluginsNum=1;
                }
                if(1==Parameter::Camera_Load_Plugin){
                    pluginsNum=channelCount*LocalPar::CamerNumber;
                }

                if(4==Parameter::HCNET_Capture_Type){
                    if("Underlying" == pIMiddleware->InterfaceType()){
                        loadMisarrangement(pluginName,"Underlying");
                    }
                    else {
                        pluginsNum=0;
                    }
                }
                else {
                    if ("HCNET" == pIMiddleware->InterfaceType()) {
                        loadMisarrangement(pluginName,"HCNET");
                    }
                    else {
                        pluginsNum=0;
                    }
                }

                /*****************************
                * @brief:所有海康车牌使用一个库
                ******************************/
                if(0==Parameter::PlateType && "HCNET" == pIMiddleware->InterfaceType()){
                    pluginsNum+=1;
                }

                pIMiddleware=nullptr;
            }
            else if (InfraredlogicInterface *pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)) {
                if(0==Parameter::LogicType){
                    if("Protector" == pInfraredlogicInterface->InterfaceType()){/* 电泳保护器 */
                        pluginsNum=channelCount;
                        loadMisarrangement(pluginName,"Protector");
                    }
                }
                if(1==Parameter::LogicType){
                    if("Protector_NJSB" == pInfraredlogicInterface->InterfaceType()){/* 电泳保护器 */
                        pluginsNum=channelCount;
                        loadMisarrangement(pluginName,"Protector");
                    }
                }

                pInfraredlogicInterface=nullptr;
            }
            else if (DataBaseInsertInterface *pDataBaseInsertInterface=qobject_cast<DataBaseInsertInterface*>(plugin)) {
                if("SQLITE_INSERT" == pDataBaseInsertInterface->InterfaceType()){/* SQLITE */
                    loadMisarrangement(pluginName,"SQLITE_INSERT");
                    pluginsNum=channelCount;
                }
                pDataBaseInsertInterface=nullptr;
            }
            else if (DataBaseReadInterface *pDataBaseReadInterface=qobject_cast<DataBaseReadInterface*>(plugin)) {
                if("SQLITE_READ" == pDataBaseReadInterface->InterfaceType()){/* SQLITE */
                    loadMisarrangement(pluginName,"SQLITE_READ");
                    pluginsNum=1;
                }
                pDataBaseReadInterface=nullptr;
            }
            else if (RecognizerInterface *pRecognizerInterface=qobject_cast<RecognizerInterface*>(plugin)) {
                if("ImageIdentify"==pRecognizerInterface->InterfaceType()){/* 识别图片 */
                    loadMisarrangement(pluginName,"ImageIdentify");
                    pluginsNum=channelCount;
                }
                pDataBaseReadInterface=nullptr;
            }
            else if (ResultsAnalysisInterface *pResultsAnalysisInterface=qobject_cast<ResultsAnalysisInterface*>(plugin)) {
                if("ResultsAnalysis"==pResultsAnalysisInterface->InterfaceType()){/* 结果分析 */
                    loadMisarrangement(pluginName,"ResultsAnalysis");
                    pluginsNum=channelCount;
                }
                pResultsAnalysisInterface=nullptr;
            }
            else if (ToUploadDataInterface *pToUploadDataInterface=qobject_cast<ToUploadDataInterface*>(plugin)) {
                if("FTP"==pToUploadDataInterface->InterfaceType()){/* 上传图片 */
                    loadMisarrangement(pluginName,"FTP");
                    pluginsNum=1;
                }
                pToUploadDataInterface=nullptr;
            }
            else if (DataInterchangeInterface *pDataInterchangeInterface=qobject_cast<DataInterchangeInterface*>(plugin)) {
                if(0==Parameter::DataChaneType && "TCP"==pDataInterchangeInterface->InterfaceType()){/* 数据传输 */
                    loadMisarrangement(pluginName,"TCP");
                    if(Parameter::Service_Type || Parameter::DataChaneType==1){
                        pluginsNum=1;
                    }
                    else {
                        pluginsNum=channelCount;
                    }
                }
                else if (1==Parameter::DataChaneType && "MQ"==pDataInterchangeInterface->InterfaceType()) {
                    loadMisarrangement(pluginName,"MQ");
                    if(Parameter::Service_Type || Parameter::DataChaneType==1){
                        pluginsNum=1;
                    }
                    else {
                        pluginsNum=channelCount;
                    }
                }
                pDataInterchangeInterface=nullptr;
            }
            else if(LicensePlateInterface *pLicensePlateInterface=qobject_cast<LicensePlateInterface*>(plugin)){
                if(0==Parameter::PlateType && "HCNET_PLATE"==pLicensePlateInterface->InterfaceType()){/* 海康车牌 */
                    loadMisarrangement(pluginName,"HCNET_PLATE");
                    pluginsNum=channelCount;
                }
                else if (1==Parameter::PlateType && "WTY_PLATE"==pLicensePlateInterface->InterfaceType()) {
                    loadMisarrangement(pluginName,"WTY_PLATE");
                    pluginsNum=channelCount;
                }
                pLicensePlateInterface=nullptr;
            }
            else if(EncryptionInterface *pEncryptionInterface=qobject_cast<EncryptionInterface*>(plugin)){
                pluginsNum=1;/* 加密 */
                pEncryptionInterface=nullptr;
            }
            else {
                emit signal_loadPluginError(fileName);/* 加载插件插件报错 */
            }

            if(pluginsNum>0){
                for(int i=1;i<=pluginsNum;i++){
                    QFile::copy(QDir::toNativeSeparators(QString("%1/%2").arg(path).arg(fileName)),QDir::toNativeSeparators(QString("%1/%2_%3").arg(pluginsDir.absolutePath()).arg(i).arg(fileName)));
                }
                processingPlugins(pluginsDir);
            }
            else {
                //emit signal_loadPluginError(fileName);/* 加载插件插件报错 */
            }

            pluginsDir.cdUp();
        }
        pluginLoader.unload();
    }
    emit signal_handleFinished();
}

void LoadingLibaray::processingPlugins(QDir pluginPath)
{
    emit signal_progressRangeChanged(0,pluginPath.entryList(QDir::Files).count());
    int val=1;

    const QStringList entryList=pluginPath.entryList(QDir::Files);
    for(QString pluginName:entryList){

        emit signal_progressValueChanged(val++);
        emit signal_progressTextChanged(pluginName);

        QPluginLoader  pluginLoader(pluginPath.absoluteFilePath(pluginName));
        QObject* plugin = pluginLoader.instance();

        if(plugin){
            if(ICaptureImages *pICaptureImages=qobject_cast<ICaptureImages*>(plugin)){
                QThread *th=new QThread(this);
                tdList.append(th);
                pICaptureImages->moveToThread(th);
                th->start();
                ICaptureImagesLit.append(QSharedPointer<ICaptureImages>(pICaptureImages));                
            }
            else if(IMiddleware *pIMiddleware=qobject_cast<IMiddleware*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pIMiddleware->moveToThread(th);
                th->start();
                IMiddlewareLit.append(QSharedPointer<IMiddleware>(pIMiddleware));
            }
            else if (InfraredlogicInterface *pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pInfraredlogicInterface->moveToThread(th);
                th->start();
                InfraredlogicLit.append(QSharedPointer<InfraredlogicInterface>(pInfraredlogicInterface));
            }
            else if (DataBaseInsertInterface *pDataBaseInsertInterface=qobject_cast<DataBaseInsertInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pDataBaseInsertInterface->moveToThread(th);
                th->start();
                IDataBaseInsertList.append(QSharedPointer<DataBaseInsertInterface>(pDataBaseInsertInterface));
            }
            else if (DataBaseReadInterface *pDataBaseReadInterface=qobject_cast<DataBaseReadInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pDataBaseReadInterface->moveToThread(th);
                th->start();
                IDataBaseReadList.append(QSharedPointer<DataBaseReadInterface>(pDataBaseReadInterface));
            }
            else if (RecognizerInterface *pRecognizerInterface=qobject_cast<RecognizerInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pRecognizerInterface->moveToThread(th);
                th->start();
                IRecognizerList.append(QSharedPointer<RecognizerInterface>(pRecognizerInterface));
            }
            else if (ResultsAnalysisInterface *pResultsAnalysisInterface=qobject_cast<ResultsAnalysisInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pResultsAnalysisInterface->moveToThread(th);
                th->start();
                IResultsAnalysisList.append(QSharedPointer<ResultsAnalysisInterface>(pResultsAnalysisInterface));
            }
            else if (DataInterchangeInterface *pDataInterchangeInterface=qobject_cast<DataInterchangeInterface*>(plugin)) {
//                QThread *th=new QThread(this);
//                tdList.append(th);
//                pDataInterchangeInterface->moveToThread(th);
//                th->start();
                IDataInterchangeList.append(QSharedPointer<DataInterchangeInterface>(pDataInterchangeInterface));
            }
            else if (ToUploadDataInterface *pToUploadDataInterface=qobject_cast<ToUploadDataInterface*>(plugin)) {
                QThread *th=new QThread(this);
                tdList.append(th);
                pToUploadDataInterface->moveToThread(th);
                th->start();
                IToUploadDataList.append(QSharedPointer<ToUploadDataInterface>(pToUploadDataInterface));
            }
            else if(LicensePlateInterface *pLicensePlateInterface=qobject_cast<LicensePlateInterface*>(plugin)){
                QThread *th=new QThread(this);
                tdList.append(th);
                pLicensePlateInterface->moveToThread(th);
                th->start();
                ILicensePlateList.append(QSharedPointer<LicensePlateInterface>(pLicensePlateInterface));
            }
            else if(EncryptionInterface *pEncryptionInterface=qobject_cast<EncryptionInterface*>(plugin)){
                QThread *th=new QThread(this);
                tdList.append(th);
                pEncryptionInterface->moveToThread(th);
                th->start();
                IEncryptionList.append(QSharedPointer<EncryptionInterface>(pEncryptionInterface));
            }
            else {
                pluginLoader.unload();
            }
        }
        else{
            pluginLoader.unload();
        }
    }
}
