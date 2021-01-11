﻿#include "loadinglibaray.h"
#include <QtDebug>

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
    qDebug().noquote()<<"~LoadingLibaray";
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

    /*****************************
    * @brief:加载插件名称，判断同一接口是否重复加载
    ******************************/
    QVector<QString> loadVec;

    for(const QString fileName :pluginsDir.entryList(QDir::Files,QDir::Name)){
        QPluginLoader  pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();

        if(plugin){
//            QJsonObject var=pluginLoader.metaData();
//            qDebug()<<var.find("MetaData").value().toString();

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

            bool isErr=false;

            if(ICaptureImages *pICaptureImages=qobject_cast<ICaptureImages*>(plugin)){
                delete pICaptureImages;
                pICaptureImages=nullptr;
                pluginsNum=channelCount*LocalPar::CamerNumber;

                if(-1!=loadVec.indexOf("ICaptureImages")){
                    isErr=true;
                }
                else {
                    loadVec.append("ICaptureImages");
                }
            }
            else if(IMiddleware *pIMiddleware=qobject_cast<IMiddleware*>(plugin)) {
                if("HCNET" == pIMiddleware->InterfaceType()){/* 海康相机 */
                    delete pIMiddleware;
                    pIMiddleware=nullptr;
                    //pluginsNum=1;
                    pluginsNum=channelCount*LocalPar::CamerNumber;
                }
            }
            else if (InfraredlogicInterface *pInfraredlogicInterface=qobject_cast<InfraredlogicInterface*>(plugin)) {
                if("Protector" == pInfraredlogicInterface->InterfaceType()){/* 电泳保护器 */
                    delete pInfraredlogicInterface;
                    pInfraredlogicInterface=nullptr;
                    pluginsNum=channelCount;
                }
            }
            else if (DataBaseInsertInterface *pDataBaseInsertInterface=qobject_cast<DataBaseInsertInterface*>(plugin)) {
                if("SQLITE" == pDataBaseInsertInterface->InterfaceType()){/* SQLITE */
                    delete pDataBaseInsertInterface;
                    pDataBaseInsertInterface=nullptr;
                    pluginsNum=channelCount;
                }
            }
            else if (DataBaseReadInterface *pDataBaseReadInterface=qobject_cast<DataBaseReadInterface*>(plugin)) {
                if("SQLITE" == pDataBaseReadInterface->InterfaceType()){/* SQLITE */
                    delete pDataBaseReadInterface;
                    pDataBaseReadInterface=nullptr;
                    pluginsNum=1;
                }
            }
            else if (RecognizerInterface *pRecognizerInterface=qobject_cast<RecognizerInterface*>(plugin)) {
                if("ImageIdentify"==pRecognizerInterface->InterfaceType()){/* 识别图片 */
                    delete pRecognizerInterface;
                    pRecognizerInterface=nullptr;
                    pluginsNum=channelCount;
                }
            }
            else if (ResultsAnalysisInterface *pResultsAnalysisInterface=qobject_cast<ResultsAnalysisInterface*>(plugin)) {
                if("ResultsAnalysis"==pResultsAnalysisInterface->InterfaceType()){
                    delete pResultsAnalysisInterface;
                    pResultsAnalysisInterface=nullptr;
                    pluginsNum=channelCount;
                }
            }
            else if (DataInterchangeInterface *pDataInterchangeInterface=qobject_cast<DataInterchangeInterface*>(plugin)) {
                if("DataInterchange"==pDataInterchangeInterface->InterfaceType()){
                    delete pDataInterchangeInterface;
                    pDataInterchangeInterface=nullptr;
                    if(Parameter::Service_Type){
                        pluginsNum=1;
                    }
                    else {
                        pluginsNum=channelCount;
                    }
                }
            }
            else {
                if(0==pluginsNum){
                    emit signal_loadPluginError(fileName);/* 加载插件插件报错 */
                }
                pluginLoader.unload();
            }

            if(isErr){
                emit signal_loadPluginError(fileName);/* 加载相同插件多次报错 */
            }

            for(int i=1;i<=pluginsNum;i++){
                  QFile::copy(QDir::toNativeSeparators(QString("%1/%2").arg(path).arg(fileName)),QDir::toNativeSeparators(QString("%1/%2_%3").arg(pluginsDir.absolutePath()).arg(i).arg(fileName)));
            }
            if(pluginsNum>0){
                processingPlugins(pluginsDir);
            }

            pluginsDir.cdUp();
        }       
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
                QThread *th=new QThread(this);
                tdList.append(th);
                pDataInterchangeInterface->moveToThread(th);
                th->start();
                IDataInterchangeList.append(QSharedPointer<DataInterchangeInterface>(pDataInterchangeInterface));
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