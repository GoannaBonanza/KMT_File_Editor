#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "KMT.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_currentIndexChanged(int index) //character updated
{
    entry->setCharacter(index);
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index) //vehicle updated
{
    entry->setVehicle(index);
}


void MainWindow::on_pushButton_clicked() //save clicked
{
    file.writeFile(filename);
}


void MainWindow::on_pushButton_2_clicked() //open clicked
{
    try{file.open(filename);}
    catch(...){
        ui->problemLabel->setText("Unable to open file");
        return;
    }
    ui->problemLabel->setText("File opened");
    entry=&file[(level-1)*8+sublevel-1];
    load();
}


void MainWindow::on_comboBox_33_currentIndexChanged(int index) //course updated
{
    index=index<0x2a?index:index==0x2a?0x37:index==0x2b?0x38:index==0x2c?0x3a:0x36;
    entry->setCourse(index);
}


void MainWindow::on_spinBox_2_valueChanged(int arg1) //time limit changed
{
    entry->setTimeLimit(arg1);
}


void MainWindow::on_spinBox_3_valueChanged(int arg1) //score changed
{
    entry->setScoreRequired(arg1);
}


void MainWindow::on_comboBox_5_currentIndexChanged(int index) //gamemode updated
{
    entry->setGamemode(index);
}


void MainWindow::on_checkBox_2_stateChanged(int arg1) //cannon flag check changed
{
    arg1=arg1==2?1:0;
    entry->setCannonFlag(arg1);
}


void MainWindow::on_checkBox_stateChanged(int arg1) //camera angle check changed
{
    arg1=arg1==2?7:3;
    entry->setCameraMode(arg1);
}


void MainWindow::on_spinBox_valueChanged(int arg1) //level number changed
{
    level=arg1;
    entry=&file[(level-1)*8+sublevel-1];
    load();
}


void MainWindow::on_spinBox_4_valueChanged(int arg1) //sublevel value changed
{
    sublevel=arg1;
    entry=&file[(level-1)*8+sublevel-1];
    load();
}


void MainWindow::on_pushButton_7_clicked()//50cc pushed
{
    entry->setEngineClass(0);
    ui->ccLabel->setText("Current: 50cc");
}


void MainWindow::on_pushButton_8_clicked()//100cc pushed
{
    entry->setEngineClass(1);
    ui->ccLabel->setText("Current: 100cc");
}


void MainWindow::on_pushButton_9_clicked()//150cc pushed
{
    entry->setEngineClass(2);
    ui->ccLabel->setText("Current: 150cc");
}

//loads current entry into main window
void MainWindow::load(){
    for(unsigned char i=1; i<12; i++) deaCPU(i);
    entry=&file[(level-1)*8+sublevel-1];
    ui->comboBox->setCurrentIndex(entry->getChar());
    ui->comboBox_2->setCurrentIndex(entry->getVeh());
    switch(entry->getCourse()){
    case 0x36:
        ui->comboBox_33->setCurrentIndex(0x2d);
        break;
    case 0x37:
        ui->comboBox_33->setCurrentIndex(0x2a);
        break;
    case 0x38:
        ui->comboBox_33->setCurrentIndex(0x2b);
        break;
    case 0x3a:
        ui->comboBox_33->setCurrentIndex(0x2c);
        break;
    default:
        ui->comboBox_33->setCurrentIndex(entry->getCourse());
        break;
    }
    ui->comboBox_5->setCurrentIndex(entry->getGamemode());
    ui->spinBox_2->setValue(entry->getTime());
    ui->spinBox_3->setValue(entry->getScore());
    ui->checkBox->setChecked(entry->getCamera()==7);
    ui->checkBox_2->setChecked(entry->getCannon()==1);
    switch (entry->getCC()){
    case 0:
        ui->ccLabel->setText("Current: 50cc");
        break;
    case 1:
        ui->ccLabel->setText("Current: 100cc");
        break;
    default:
        ui->ccLabel->setText("Current: 150cc");
        break;
    }
    for(unsigned char i=0; i<entry->cpucount(); i++){
        enaCPU(i);
    }
}
//for ease of adding CPUs
void MainWindow::enaCPU(unsigned int n){
    switch(n){
    case 0:
        ui->cpu1c->setEnabled(true);
        ui->cpu1c->setCurrentIndex(entry->getCPUCha(0));
        ui->cpu1v->setEnabled(true);
        ui->cpu1v->setCurrentIndex(entry->getCPUVeh(0));
        break;
    case 1:
        ui->cpu2c->setEnabled(true);
        ui->cpu2c->setCurrentIndex(entry->getCPUCha(1));
        ui->cpu2v->setEnabled(true);
        ui->cpu2v->setCurrentIndex(entry->getCPUVeh(1));
        break;
    case 2:
        ui->cpu3c->setEnabled(true);
        ui->cpu3c->setCurrentIndex(entry->getCPUCha(2));
        ui->cpu3v->setEnabled(true);
        ui->cpu3v->setCurrentIndex(entry->getCPUVeh(2));
        break;
    case 3:
        ui->cpu4c->setEnabled(true);
        ui->cpu4c->setCurrentIndex(entry->getCPUCha(3));
        ui->cpu4v->setEnabled(true);
        ui->cpu4v->setCurrentIndex(entry->getCPUVeh(3));
        break;
    case 4:
        ui->cpu5c->setEnabled(true);
        ui->cpu5c->setCurrentIndex(entry->getCPUCha(4));
        ui->cpu5v->setEnabled(true);
        ui->cpu5v->setCurrentIndex(entry->getCPUVeh(4));
        break;
    case 5:
        ui->cpu6c->setEnabled(true);
        ui->cpu6c->setCurrentIndex(entry->getCPUCha(5));
        ui->cpu6v->setEnabled(true);
        ui->cpu6v->setCurrentIndex(entry->getCPUVeh(5));
        break;
    case 6:
        ui->cpu7c->setEnabled(true);
        ui->cpu7c->setCurrentIndex(entry->getCPUCha(6));
        ui->cpu7v->setEnabled(true);
        ui->cpu7v->setCurrentIndex(entry->getCPUVeh(6));
        break;
    case 7:
        ui->cpu8c->setEnabled(true);
        ui->cpu8c->setCurrentIndex(entry->getCPUCha(7));
        ui->cpu8v->setEnabled(true);
        ui->cpu8v->setCurrentIndex(entry->getCPUVeh(7));
        break;
    case 8:
        ui->cpu9c->setEnabled(true);
        ui->cpu9c->setCurrentIndex(entry->getCPUCha(8));
        ui->cpu9v->setEnabled(true);
        ui->cpu9v->setCurrentIndex(entry->getCPUVeh(8));
        break;
    case 9:
        ui->cpu10c->setEnabled(true);
        ui->cpu10c->setCurrentIndex(entry->getCPUCha(9));
        ui->cpu10v->setEnabled(true);
        ui->cpu10v->setCurrentIndex(entry->getCPUVeh(9));
        break;
    case 10:
        ui->cpu11c->setEnabled(true);
        ui->cpu11c->setCurrentIndex(entry->getCPUCha(10));
        ui->cpu11v->setEnabled(true);
        ui->cpu11v->setCurrentIndex(entry->getCPUVeh(10));
        break;
    default:
        break;
    }
}
void MainWindow::deaCPU(unsigned int n){
    switch(n){
    case 1:
        ui->cpu1c->setEnabled(false);
        ui->cpu1c->setCurrentIndex(0);
        ui->cpu1v->setEnabled(false);
        ui->cpu1v->setCurrentIndex(0);
        break;
    case 2:
        ui->cpu2c->setEnabled(false);
        ui->cpu2c->setCurrentIndex(0);
        ui->cpu2v->setEnabled(false);
        ui->cpu2v->setCurrentIndex(0);
        break;
    case 3:
        ui->cpu3c->setEnabled(false);
        ui->cpu3c->setCurrentIndex(0);
        ui->cpu3v->setEnabled(false);
        ui->cpu3v->setCurrentIndex(0);
        break;
    case 4:
        ui->cpu4c->setEnabled(false);
        ui->cpu4c->setCurrentIndex(0);
        ui->cpu4v->setEnabled(false);
        ui->cpu4v->setCurrentIndex(0);
        break;
    case 5:
        ui->cpu5c->setEnabled(false);
        ui->cpu5c->setCurrentIndex(0);
        ui->cpu5v->setEnabled(false);
        ui->cpu5v->setCurrentIndex(0);
        break;
    case 6:
        ui->cpu6c->setEnabled(false);
        ui->cpu6c->setCurrentIndex(0);
        ui->cpu6v->setEnabled(false);
        ui->cpu6v->setCurrentIndex(0);
        break;
    case 7:
        ui->cpu7c->setEnabled(false);
        ui->cpu7c->setCurrentIndex(0);
        ui->cpu7v->setEnabled(false);
        ui->cpu7v->setCurrentIndex(0);
        break;
    case 8:
        ui->cpu8c->setEnabled(false);
        ui->cpu8c->setCurrentIndex(0);
        ui->cpu8v->setEnabled(false);
        ui->cpu8v->setCurrentIndex(0);
        break;
    case 9:
        ui->cpu9c->setEnabled(false);
        ui->cpu9c->setCurrentIndex(0);
        ui->cpu9v->setEnabled(false);
        ui->cpu9v->setCurrentIndex(0);
        break;
    case 10:
        ui->cpu10c->setEnabled(false);
        ui->cpu10c->setCurrentIndex(0);
        ui->cpu10v->setEnabled(false);
        ui->cpu10v->setCurrentIndex(0);
        break;
    case 11:
        ui->cpu11c->setEnabled(false);
        ui->cpu11c->setCurrentIndex(0);
        ui->cpu11v->setEnabled(false);
        ui->cpu11v->setCurrentIndex(0);
        break;
    default:
        break;
    }
}
//CPU ComboBoxes YAY

void MainWindow::on_cpu1c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 0);
}
void MainWindow::on_cpu1v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 0);
}
void MainWindow::on_cpu2c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 1);
}
void MainWindow::on_cpu2v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 1);
}
void MainWindow::on_cpu3c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 2);
}
void MainWindow::on_cpu3v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 2);
}
void MainWindow::on_cpu4c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 3);
}
void MainWindow::on_cpu4v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 3);
}
void MainWindow::on_cpu5c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 4);
}
void MainWindow::on_cpu5v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 4);
}
void MainWindow::on_cpu6c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 5);
}
void MainWindow::on_cpu6v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 5);
}
void MainWindow::on_cpu7c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 6);
}
void MainWindow::on_cpu7v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 6);
}
void MainWindow::on_cpu8c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 7);
}
void MainWindow::on_cpu8v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 7);
}
void MainWindow::on_cpu9c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 8);
}
void MainWindow::on_cpu9v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 8);
}
void MainWindow::on_cpu10c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 9);
}
void MainWindow::on_cpu10v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 9);
}
void MainWindow::on_cpu11c_currentIndexChanged(int index)
{
    entry->setCPUCha(index, 10);
}
void MainWindow::on_cpu11v_currentIndexChanged(int index)
{
    entry->setCPUVeh(index, 10);
}


void MainWindow::on_removeCPU_clicked()
{
    deaCPU(entry->cpucount());
    entry->popCPU();
}


void MainWindow::on_addCPU_clicked()
{
    enaCPU(entry->cpucount());
    entry->addCPU();
}

