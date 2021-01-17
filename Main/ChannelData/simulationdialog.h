﻿#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDateTime>

namespace Ui {
class SimulationDialog;
}

class SimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationDialog(int channelNumber,QWidget *parent = nullptr);
    ~SimulationDialog();

private slots:
    void on_capturePushButton_clicked();

    void on_plateCapPushButton_clicked();

    void on_liftingLeverPushButton_clicked();

    void on_fallRodPushButton_clicked();

    void on_toolButton_clicked();

    void on_while_cycle_capture_checkBox_stateChanged(int arg1);

    void slot_timerCap();

    void slot_whileCap();

    void on_pushButton_clicked();

public slots:

    ///
    /// \brief slot_container 结果集
    /// \param type
    /// \param result1
    /// \param resultCheck1
    /// \param iso1
    /// \param result2
    /// \param resultCheck2
    /// \param iso2
    ///
    void slot_container(const int &type, const QString &result1, const int &resultCheck1, const QString &iso1, const QString &result2, const int &resultCheck2, const QString &iso2);


private:
    Ui::SimulationDialog *ui;
    QTimer *timer;

    int col;
    int channelNumber;

signals:

    ///
    /// \brief signal_logicPutImage 模拟抓拍
    /// \param putCommnd
    ///
    void signal_logicPutImage(const int &putCommnd);

    ///
    /// \brief sendResultSignal 发送识别结果
    /// \param channel 通道号
    /// \param result 识别结果
    ///
    void sendResultSignal(int channel,const QString& result);
};

#endif // SIMULATIONDIALOG_H
