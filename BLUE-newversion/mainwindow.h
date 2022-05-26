#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include<QFileDialog>
#include<QString>
#include<QVideoWidget>
#include <QtCore>
#include <QtGui>
#include "QMediaPlaylist.h"
#include <QMediaMetaData>
#include <QLabel>
#include "PlaylistModel.h"
#include <qlistview.h>
#include "QAbstractItemView"
#include "ui_mainwindow.h"
#include<QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addToPlaylist(const QList<QUrl> &urls);
    bool isPlayerAvailable() const;
    void open();
    void timerUpdate();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event); //鼠标事件重写--悬浮窗
    virtual void keyPressEvent(QKeyEvent* event);//键盘事件重写--音量快捷键
    virtual void paintEvent(QPaintEvent *event);//绘图事件重写--窗口自适应

private slots:

//视频轨道相关槽
    void mediaStateChanged(QMediaPlayer::PlaybackState state);//播放状态
    void positionChanged(qint64 position);//改变播放位置
    void durationChanged(qint64 position);//改变播放长度
    void setPosition(int position);//获取播放位置

//播放时间文字槽函数
    void setduration(qint64 dur);
    void setpassedtime(qint64 passedtime);

//音频轨道相关槽
    void setVolume(int position);//改变音量大小

//播放相关槽函数
    void play();
    void playlistPositionChanged(int currentItem)
    {
        if (ui->m_playlistView)
            ui->m_playlistView->setCurrentIndex(m_playlistModel->index(currentItem, 0));
        mediaPlayer->setSource(m_playlist->currentMedia());
    }

    void jump(const QModelIndex &index)
    {
        if (index.isValid()) {
            m_playlist->setCurrentIndex(index.row());
        }
        mediaPlayer->play();
    }
    void tracksChanged();

//ui槽函数
    void on_openfilebtn_clicked();
    void on_playbtn_clicked();
    void on_prebtn_clicked();
    void on_nextbtn_clicked();
    void on_PlayMode_clicked();
    void on_ratebtn_clicked();
    void on_volumebtn_clicked();
    void on_fullscreenbtn_clicked();
    void on_progressbar_sliderMoved(int position);




Q_SIGNALS:
       void EndOfMedia();
private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *vedioWidget;
    QAudioOutput* audioOutput=nullptr;
    QMediaPlaylist *m_playlist = nullptr;
    PlaylistModel *m_playlistModel = nullptr;

    QWidget *m_metaDataFields[QMediaMetaData::NumMetaData] = {};
    QLabel *m_metaDataLabels[QMediaMetaData::NumMetaData] = {};


};
#endif // MAINWINDOW_H
