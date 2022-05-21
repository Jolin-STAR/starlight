#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include<QFileDialog>
#include<QString>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;//QVideoWidget

private slots:
    //播放与播放槽函数
    void play();
    void mediaStateChanged(QMediaPlayer::PlaybackState state);//播放状态
    void positionChanged(qint64 position);//改变播放位置
    void setPosition(int position);//获取播放位置
    void durationChanged(qint64 position);//改变播放长度
    void on_play_clicked();
    void on_horizontalSlider_sliderMoved(int position);

//    //异常播出
//    void handleError();

    void on_OpenFile_clicked();
};
#endif // MAINWINDOW_H
