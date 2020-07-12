#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QResizeEvent>
#include <QDesktopWidget>
#include <QMap>
#include <QAction>
#include <QLabel>

/* UI */
#include "Channel_Data/channel_data_form.h"
#include "Channel_Data/equipment_state_from.h"
#include "Setting/setting_form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()Q_DECL_OVERRIDE;

private:

    /*****************************
    * Func
    ******************************/

    ///
    /// \brief removeTheWindow 显示窗口之前要删除其他窗口
    ///
    void removeTheWindow();

    ///
    /// \brief initializingObject 初始化对象
    ///
    void initializingObject();

    ///
    /// \brief initializationParameter 初始化参数
    ///
    void initializationParameter();

    ///
    /// \brief clearnMap 清除容器
    ///
    void clearnContainer();

    ///
    /// \brief setStatusBar 设置状态栏信息
    ///
    void setStatusBar(QString msg);

    ///
    /// \brief mainWindow 主窗口信号与槽
    ///
    void mainConnect();

    ///
    /// \brief fromConnet 子窗口信号与槽
    ///
    void fromConnet();

    ///
    /// \brief initStatusBar 初始化状态栏
    ///
    void initStatusBar();

    ///
    /// \brief getScreenInfo 获取和设置系统屏幕大小
    ///
    void getScreenInfo();

private slots:

    /*****************************
    * Slot
    ******************************/

    ///
    /// \brief actionTiggeredSlot 工具栏按钮事件
    ///
    void actionTiggeredSlot();

    ///
    /// \brief on_actionMainWindow_triggered 显示主页面
    ///
    void on_actionMainWindow_triggered();

    ///
    /// \brief on_actionSystem_Settings_triggered 系统设置
    ///
    void on_actionSystem_Settings_triggered();

    //test
    void on_actiontest_triggered();

signals:

    /*****************************
    * Signal
    ******************************/

    ///
    /// \brief initializesTheDeviceStateListSignal 初始化设备状态列表
    /// \param count 通道数
    /// \param rowLabels 通道名称
    ///
    void initializesTheDeviceStateListSignal(int count,QStringList rowLabels);

    ///
    /// \brief setDeviceStatusSignal 设置设备表状态
    /// \param channel 通道
    /// \param equipment 设备
    /// \param state 状态
    ///
    void setDeviceStatusSignal(int channel, int equipment,bool state);

private:

    /*****************************
    * The container
    ******************************/

    ///
    /// \brief WindowsVector 窗口集
    ///
    QVector<QObject*> WindowsVector;

    ///
    /// \brief Channel_Data_Action_Map 数据窗口工具栏字典集
    ///
    QMap<QAction*,int> Channel_Data_Action_Map;

private:

    /*****************************
    * attribute
    ******************************/

    ///
    /// \brief channelSelect 数据界面组中,当前预览的通道号
    ///
    int channelSelect;

    ///
    /// \brief channelCount 通道数
    ///
    int channelCount=1;

    ///
    /// \brief channelLabels 通道名称列表
    ///
    QStringList channelLabels;

private:

    /*****************************
    * object
    ******************************/

    Ui::MainWindow *ui;

    ///
    /// \brief pFrom 数据窗口
    ///
    Channel_Data_Form *p_Channel_Data_Form=nullptr;

    ///
    /// \brief p_Equipment_State_From 设备列表窗口
    ///
    Equipment_State_From *p_Equipment_State_From=nullptr;

    ///
    /// \brief p_Setting_From 设置窗口
    ///
    Setting_Form *p_Setting_From=nullptr;

    ///
    /// \brief permanentWidget 状态栏永久信息
    ///
    QLabel *permanentWidget=nullptr;
};

#endif // MAINWINDOW_H
