﻿#ifndef LOADINGLIBARAY_H
#define LOADINGLIBARAY_H

#include <QObject>
#include <QPluginLoader>
#include <QCoreApplication>
#include <QDir>
#include <QThread>

#include "LocalPar.h"
#include "parameter.h"

#include "interface/ICaptureImages.h"
#include "interface/IMiddleware.h"
#include "interface/infraredlogicinterface.h"
#include "interface/databaseinsertinterface.h"
#include "interface/databasereadinterface.h"
#include "interface/recognizerinterface.h"
#include "interface/resultsanalysisinterface.h"
#include "interface/datainterchangeinterface.h"

class LoadingLibaray : public QObject
{
    Q_OBJECT

public:

    ///
    /// \brief LoadingLibaray 创建插件
    /// \param ChannelNumber 通道数量
    /// \param parent
    ///
    explicit LoadingLibaray(int ChannelNumber,QObject *parent = nullptr);

private:

    int channelCount;

    ///
    /// \brief tdList 子线程集
    ///
    QList<QThread*> tdList;

    ///
    /// \brief processingPlugins 加载插件到内存
    /// \param pluginPath 插件路径
    ///
    void processingPlugins(QDir pluginPath);

public:/* container */

    ///
    /// \brief ICaptureImagesLit 相机插件库
    ///
    QList<QSharedPointer<ICaptureImages>> ICaptureImagesLit;

    ///
    /// \brief IMiddlewareLit 相机中间件插件库
    ///
    QList<QSharedPointer<IMiddleware>> IMiddlewareLit;

    ///
    /// \brief InfraredlogicLit 红外插件库
    ///
    QList<QSharedPointer<InfraredlogicInterface>> InfraredlogicLit;

    ///
    /// \brief IDataBaseInsertList 数据库插入库
    ///
    QList<QSharedPointer<DataBaseInsertInterface>> IDataBaseInsertList;

    ///
    /// \brief IDataBaseReadList 数据库读取库
    ///
    QList<QSharedPointer<DataBaseReadInterface>> IDataBaseReadList;

    ///
    /// \brief IRecognizerList 识别器库
    ///
    QList<QSharedPointer<RecognizerInterface>> IRecognizerList;

    ///
    /// \brief IResultsAnalysisList 结果分析库
    ///
    QList<QSharedPointer<ResultsAnalysisInterface>> IResultsAnalysisList;

    ///
    /// \brief IDataInterchangeList 数据协议对接
    ///
    QList<QSharedPointer<DataInterchangeInterface>> IDataInterchangeList;

public slots:

    ///
    /// \brief slot_createLibaray 加载插件
    ///
    void slot_createLibaray();

    ///
    /// \brief slot_destructorThread 析构插件线程
    ///
    void slot_destructorThread();

signals:

    ///
    /// \brief signal_handleFinished 异步加载插件完成
    ///
    void signal_handleFinished();

    ///
    /// \brief signal_progressRangeChanged 异步加载插件设置进度条范围
    /// \param minimum
    /// \param maximum
    ///
    void signal_progressRangeChanged(int minimum, int maximum);

    ///
    /// \brief signal_progressTextChanged 异步加载插件设置进度条文本
    /// \param progressText
    ///
    void signal_progressTextChanged(const QString &progressText);

    ///
    /// \brief signal_progressValueChanged 异步加载插件设置进度条值
    /// \param progressValue
    ///
    void signal_progressValueChanged(int progressValue);

    ///
    /// \brief signal_loadPluginError 加载插件异常，出现重复插件
    /// \param pluginName
    ///
    void signal_loadPluginError(QString pluginName);

};

#endif // LOADINGLIBARAY_H