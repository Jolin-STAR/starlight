//播放基本设置
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主界面背景
    QPixmap pixmap(":/images/background.jpg");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);

    //创建mediaPlayer
    mediaPlayer=new QMediaPlayer(this);
    //设置QMediaPlayer对应的QVideoWidget播放窗口
    mediaPlayer->setVideoOutput(ui->widget);

    //设置界面按钮
    //打开文件按钮【暂时调不了】！！！！

    ui->previous->setToolTip("上一首");
    ui->previous->setAutoRaise(true);
    ui->previous->setIcon(QPixmap(":/images/the former.jpeg"));

    ui->play->setToolTip("播放");
    ui->play->setAutoRaise(true);
    ui->play->setIcon(QPixmap(":/images/play.jpeg"));

    ui->next->setToolTip("下一首");
    ui->next->setAutoRaise(true);
    ui->next->setIcon(QPixmap(":/images/the latter.jpeg"));

    ui->FullScreen->setToolTip("全屏");
    ui->FullScreen->setAutoRaise(true);
    ui->FullScreen->setIcon(QPixmap(":/images/full screen.jpeg"));

    ui->Mode->setToolTip("列表循环");
    ui->Mode->setAutoRaise(true);
    ui->Mode->setIcon(QPixmap(":/images/sequential.jpeg"));

    ui->volume->setToolTip("音量");
    ui->volume->setAutoRaise(true);
    ui->volume->setIcon(QPixmap(":/images/volume.jpeg"));



    //设置播放属性
    //监听信号变化函数
    connect(mediaPlayer,SIGNAL(stateChanged(QmediaPlayer::PlaybackState)),this,SLOT(mediaStateChanged(QMediaPlayer::PlaybackState state)));
    //播放进度变化函数
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    //播放长度信号变化
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));


}

MainWindow::~MainWindow()
{
    delete ui;
}
//播放相关槽函数
void MainWindow::on_play_clicked()
{
    play();
}
void MainWindow::play()
{//play函数根据当前的播放窗台来分别执行暂停或播放
    switch(mediaPlayer->playbackState())
    {
    case QMediaPlayer::PlayingState://处于播放状态
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}
void MainWindow::mediaStateChanged(QMediaPlayer::PlaybackState state)
{
    //播放与暂停的图标效果
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->play->setIcon(QPixmap(":/images/pause.jpeg"));
        ui->play->setToolTip("暂停");
        break;
    default:
        ui->play->setIcon(QPixmap(":/images/play.jpeg"));
        ui->play->setToolTip("播放");
        break;
    }
}
void MainWindow::positionChanged(qint64 position){
    //进度条点改变
    ui->horizontalSlider->setValue(position);
}
void MainWindow::setPosition(int position)
{
    mediaPlayer->setPosition(position);
}
void MainWindow::durationChanged(qint64 duration){
    ui->horizontalSlider->setRange(0,duration);
}



//滑动进度条事件
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}


//选择文件打开

void MainWindow::on_OpenFile_clicked()
{
    QString filename=QFileDialog::getOpenFileName();
    mediaPlayer->setSource(QUrl::fromLocalFile(filename));

}

