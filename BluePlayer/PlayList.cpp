//播放列表模型
#include "PlayList.h"
#include <qMediaPlaylist.h>
#include <QFileInfo>
#include <QUrl>

PlayList::PlayList(QObject*parent)
    :QAbstractItemModel(parent)
{
   PlayList::QPlayList.reset(new qMediaPlaylist);

}
