#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QAbstractItemModel>
#include <QScopedPointer>
#include "qMediaPlaylist.h"

//QT_BEGIN_NAMESPACE
//class qMediaPlaylist;
//QT_END_NAMESPACE

class PlayList : public QAbstractItemModel
{
    Q_OBJECT
public:
    PlayList(QObject*parent=nullptr);
    ~PlayList();

private:
    QScopedPointer<qMediaPlaylist> QPlayList; //指向播放列表的智能指针
    QMap<QModelIndex,QVariant> m_data;  //

};

#endif // PLAYLIST_H
