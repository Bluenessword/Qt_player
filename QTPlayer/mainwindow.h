#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QVideoWidget>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *mediaPlayer;

private slots:
    //播放
    void play();
    //播放状态
    void mediaStateChanged(QMediaPlayer::State state);
    //拖动进度条改动播放位置
    void positionChanged(qint64 position);
    //获取播放位置
    void setPosition(int position);
    //播放长度
    void durationChanged(qint64 duration);
    //播放异常抛出
    void handleError();

    void on_toolButton_clicked();
};

#endif // MAINWINDOW_H
