﻿#include "main_dialog.h"
#include "ui_main_dialog.h"

#include "./Parameter/LocalPar.h"
#include "./Parameter/parameter.h"
#include "./Parameter/loadparameter.h"

#include <QPointer>

Main_Dialog::Main_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_Dialog)
{
    ui->setupUi(this);   

    this->setParent(parent);
    this->setVisible(false);
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose,true);

    ui->label_2->setHidden(true);
    ui->label_7->setHidden(true);
    ui->comboBox->setHidden(true);
    ui->language_comboBox->setHidden(true);
    ui->label->setHidden(true);
    ui->ChannelNumber->setHidden(true);

    ui->ChannelNumber->setMaximum(LocalPar::Channels);
    /*****************************
    * @brief: 加载系统配置参数,【优先加载】
    ******************************/
    loadParameter();

    /*****************************
    * @brief: 设置系统模式
    ******************************/
    setSystemModel();

    /*****************************
    * @brief:倒计时启动系统
    ******************************/
    startTheTimer();
}

Main_Dialog::~Main_Dialog()
{
    delete ui;
}

void Main_Dialog::loadParameter()
{
    QPointer<LoadParameter> Pointer(new LoadParameter(this));
    if(Pointer->loadSysParameter()){
        ui->ChannelNumber->setValue(Parameter::ChannelNumber);
    }
    else {
        ui->ChannelNumber->setValue(1);
    }

    cot=Parameter::DelayStart;
    ui->verLabel->setText(LocalPar::version);
}

void Main_Dialog::setSystemModel()
{
    switch (ui->ChannelNumber->value()) {
    case 1:ui->comboBox->setCurrentIndex(0);
        break;
    default:
        ui->comboBox->setCurrentIndex(1);
    }
}

void Main_Dialog::startTheTimer()
{
    //cot=0;
    QPointer<QTimer> pPTimer=new QTimer (this);
    connect(pPTimer,SIGNAL(timeout()),this,SLOT(theCountdown()));
    pPTimer->start(1000);
}

void Main_Dialog::on_pushButton_clicked()
{
    Parameter::ChannelNumber=ui->ChannelNumber->value();
    language=ui->language_comboBox->currentIndex();
    this->done(10);
}

void Main_Dialog::on_comboBox_currentIndexChanged(int index)
{
    if(0==index){
        ui->ChannelNumber->setValue(1);
    }
}

void Main_Dialog::on_ChannelNumber_valueChanged(int arg1)
{
    if(1==arg1){
        ui->comboBox->setCurrentIndex(0);
    }
    else {
        ui->comboBox->setCurrentIndex(1);
    }    
}

void Main_Dialog::theCountdown()
{
    cot--;

    ui->pushButton->setText(QString("OK【%1】").arg(cot));

    if(0==cot){
        Parameter::ChannelNumber=ui->ChannelNumber->value();
        this->done(10);
    }
}
