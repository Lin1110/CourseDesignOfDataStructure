#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDialog>
#include <QString>
#include <iostream>
#include <fstream>
#include <memory.h>
#include <string>
#include <QObject>
#include <QApplication>
#include <QtGui>

extern int N;

typedef struct _tag_Tree{
    int father;
    char val;
    int weight;
    int Rchild;
    int Lchild;
}Tree,*TreeNode;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    char str[100] = {0};
    int w[100] = {0};
    char* path_tag;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
};
#endif // MAINWINDOW_H
