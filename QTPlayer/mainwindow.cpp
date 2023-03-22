#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建mediaPlayer
    mediaPlayer = new QMediaPlayer(this);
    //设置播放窗口
    mediaPlayer->setVideoOutput(ui->widget);
    //设置播放属性
    //1.监听播放变化信号
    connect(mediaPlayer,&QMediaPlayer::stateChanged,this,&MainWindow::mediaStateChanged);
    //2.播放进度变化信号
    connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&MainWindow::positionChanged);
    //3.播放长度变换信号
    connect(mediaPlayer,&QMediaPlayer::durationChanged,this,&MainWindow::durationChanged);
    //连接进度条和mediaPlayer
    connect(ui->horizontalSlider, &QSlider::sliderMoved, mediaPlayer, &QMediaPlayer::setPosition);
    //4.播放错误抛出异常
    connect(mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &MainWindow::handleError);

    //设置播放内容
    connect(ui->actionopen,&QAction::triggered, this, [=](){
        ui->toolButton->setEnabled(true);
        QString str = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\伟大的我\\Desktop");
        mediaPlayer->setMedia(QUrl::fromLocalFile(str));
    });

    //设置播放按钮
    ui->toolButton->setToolTip("播放");
    ui->toolButton->setIcon(QIcon(":/start.png"));
    ui->toolButton->setEnabled(false);
    ui->toolButton->setIconSize(QSize(ui->toolButton->width(),ui->toolButton->height()));
    //设置打开文件
    ui->actionopen->setToolTip("打开文件");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    //获取播放状态
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    //播放过程中动态调整播放进度
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->toolButton->setToolTip("暂停");
        ui->toolButton->setIcon(QIcon(":/stop.png"));      
        break;
    default:
        ui->toolButton->setToolTip("播放");
        ui->toolButton->setIcon(QIcon(":/start.png"));
        break;
    }
}

void MainWindow::positionChanged(qint64 position)
{
    //改变播放位置
    ui->horizontalSlider->setValue(position);
}

void MainWindow::setPosition(int position)
{
    //获取mediaplay进度条调整位置
    mediaPlayer->setPosition(position);
}

void MainWindow::durationChanged(qint64 duration)
{
    //设置进度条的范围
    ui->horizontalSlider->setRange(0, duration);
}

void MainWindow::handleError()
{
    ui->toolButton->setEnabled(false);
}


void MainWindow::on_toolButton_clicked()
{
    play();
}
