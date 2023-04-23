#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "KMT.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_33_currentIndexChanged(int index);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_comboBox_5_currentIndexChanged(int index);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void load();
    void on_cpu1c_currentIndexChanged(int index);

    void on_cpu1v_currentIndexChanged(int index);

    void on_cpu2c_currentIndexChanged(int index);

    void on_cpu2v_currentIndexChanged(int index);

    void on_cpu3c_currentIndexChanged(int index);

    void on_cpu3v_currentIndexChanged(int index);

    void on_cpu4c_currentIndexChanged(int index);

    void on_cpu4v_currentIndexChanged(int index);

    void on_cpu5c_currentIndexChanged(int index);

    void on_cpu5v_currentIndexChanged(int index);

    void on_cpu6c_currentIndexChanged(int index);

    void on_cpu6v_currentIndexChanged(int index);

    void on_cpu7c_currentIndexChanged(int index);

    void on_cpu7v_currentIndexChanged(int index);

    void on_cpu8c_currentIndexChanged(int index);

    void on_cpu8v_currentIndexChanged(int index);

    void on_cpu9c_currentIndexChanged(int index);

    void on_cpu9v_currentIndexChanged(int index);

    void on_cpu10c_currentIndexChanged(int index);

    void on_cpu10v_currentIndexChanged(int index);

    void on_cpu11c_currentIndexChanged(int index);

    void on_cpu11v_currentIndexChanged(int index);

    void enaCPU(unsigned int n);
    void deaCPU(unsigned int n);
    void on_removeCPU_clicked();

    void on_addCPU_clicked();

private:
    Ui::MainWindow *ui;
    //for ease of editing files
    KMTFile file;
    KMTEntry *entry=&file[0];
    char filename[19]="mission_single.kmt";
    int level=1, sublevel=1;
};
#endif // MAINWINDOW_H
