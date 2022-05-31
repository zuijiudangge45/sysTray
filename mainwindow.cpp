#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sysTray/systray.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sysTray *tray = new sysTray(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //忽略窗口关闭事件
    //    QApplication::setQuitOnLastWindowClosed( true );
    this->hide();
    event->ignore();
}
void MainWindow::onShowNormal(bool triggered)
{
    this->show();			//将父窗体显示
    this->activateWindow(); //将父窗口设置为活动窗口
}

void MainWindow::onShowQuit(bool triggered)
{
    qApp->exit();
}
