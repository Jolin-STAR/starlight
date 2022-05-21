//播放列表
#ifndef QMEDIAPLAYLIST_H
#define QMEDIAPLAYLIST_H

#include <QtCore/qobject.h>
#include <QtMultimedia/qtmultimediaglobal.h>
#include <QtMultimedia/qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

class qMediaPlaylist:public QObject
{
    Q_OBJECT

public:
    enum PlaybackMode{CurrentItemOnce,CurrentItemInLoop,Squential,Random};   //播放模式（只播放当前，单曲循环，顺序播放，随机播放）
    Q_ENUM(PlaybackMode)
    enum Error { NoError, FormatError, FormatNotSupportedError, AccessDeniedError };  //错误类型（）
    Q_ENUM(Error)

    qMediaPlaylist(QObject *parent = nullptr);
    ~qMediaPlaylist();

    PlaybackMode playbackMode() const; //播放模式
    void setPlaybackMode(PlaybackMode mode); //设置播放模式

    int currentIndex() const; //当前播放的媒体文件在列表中的索引
    QUrl currentMedia() const; //当前选中的媒体文件

Q_SIGNALS:
    void CurrentIndexChanged(int index); //当前索引改变信号
    void playbackModeChanged(qMediaPlaylist::PlaybackMode mode); //列表播放模式改变信号

};

QT_END_NAMESPACE

#endif // QMEDIAPLAYLIST_H
