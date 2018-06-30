#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 实例化一个对象，用来发送网络请求和接收应答
    manager = new QNetworkAccessManager(this);
    // 先隐藏进度条，开始下载时显示
    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startRequest(QUrl url)
{
    // 使用get()函数来发送网络请求
    reply = manager->get(QNetworkRequest(url));
    connect(reply,&QNetworkReply::readyRead,this,&MainWindow::httpReadyRead);
    connect(reply,&QNetworkReply::downloadProgress,this,&MainWindow::updateDataReadProgress);
    connect(reply,&QNetworkReply::finished,this,&MainWindow::httpFinished);
}

void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());

    if (fileName.isEmpty()) fileName = "index.html";
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(10);
    ui->progressBar->show();
}

void MainWindow::httpFinished()
{
    // 完成下载后重新隐藏进度条，删除reply和file对象
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();

    reply = 0;
    delete file;
    file = 0;
}

void MainWindow::httpReadyRead()
{
    // 先判断是否创建了文件，是 则读取返回的所有的数据，写入到文件
    if (file) file->write(reply->readAll());
    qWarning() << reply->readAll();
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    qWarning() << bytesRead << totalBytes;
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}
