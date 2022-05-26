#include "QMediaPlaylist.h"
#include "QMediaPlaylist_p.h"
#include "QPlaylistParser.h"

#include <QtCore/qlist.h>
#include <QtCore/qfile.h>
#include <QtCore/qurl.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qcoreapplication.h>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE

class QM3uPlaylistWriter
{
public:
    QM3uPlaylistWriter(QIODevice *device)
        :m_device(device), m_textStream(new QTextStream(m_device))
    {
    }

    ~QM3uPlaylistWriter()
    {
        delete m_textStream;
    }

    bool writeItem(const QUrl& item)
    {
        *m_textStream << item.toString() << Qt::endl;
        return true;
    }

private:
    QIODevice *m_device;
    QTextStream *m_textStream;
};


int QMediaPlaylistPrivate::nextPosition(int steps) const//下一首歌在列表中的位置
{
    if (playlist.count() == 0)//列表没有歌
        return -1;

    int next = currentPos + steps;

    switch (playbackMode) {
    case QMediaPlaylist::CurrentItemOnce://只播放该首歌一次
        return steps != 0 ? -1 : currentPos;
    case QMediaPlaylist::CurrentItemInLoop://单曲循环
        return currentPos;
    case QMediaPlaylist::Sequential://顺序播放
        if (next >= playlist.size())
            next = -1;
        break;
    case QMediaPlaylist::Loop://列表循环
        next %= playlist.count();
        break;
    }

    return next;
}

int QMediaPlaylistPrivate::prevPosition(int steps) const//前一首歌在列表中的位置
{
    if (playlist.count() == 0)
        return -1;

    int next = currentPos;//当前歌曲位置
    if (next < 0)
        next = playlist.size();
    next -= steps;

    switch (playbackMode) {
    case QMediaPlaylist::CurrentItemOnce://单曲不循环
        return steps != 0 ? -1 : currentPos;
    case QMediaPlaylist::CurrentItemInLoop://单曲循环
        return currentPos;
    case QMediaPlaylist::Sequential://顺序播放
        if (next < 0)
            next = -1;
        break;
    case QMediaPlaylist::Loop://列表循环
        next %= playlist.size();
        if (next < 0)
            next += playlist.size();
        break;
    }

    return next;
}

/*!
    \class QMediaPlaylist
    \inmodule QtMultimedia
    \ingroup multimedia
    \ingroup multimedia_playback


    \brief The QMediaPlaylist class provides a list of media content to play.

    QMediaPlaylist is intended to be used with other media objects,
    like QMediaPlayer.

    QMediaPlaylist allows to access the service intrinsic playlist functionality
    if available, otherwise it provides the local memory playlist implementation.

    \snippet multimedia-snippets/media.cpp Movie playlist

    Depending on playlist source implementation, most of the playlist mutating
    operations can be asynchronous.

    QMediaPlayList currently supports M3U playlists (file extension .m3u and .m3u8).

    \sa QUrl
*/


/*!
    \enum QMediaPlaylist::PlaybackMode

    The QMediaPlaylist::PlaybackMode describes the order items in playlist are played.

    \value CurrentItemOnce    The current item is played only once.

    \value CurrentItemInLoop  The current item is played repeatedly in a loop.

    \value Sequential         Playback starts from the current and moves through each successive item until the last is reached and then stops.
                              The next item is a null item when the last one is currently playing.

    \value Loop               Playback restarts at the first item after the last has finished playing.

    \value Random             Play items in random order.
*/


QMediaPlaylist::QMediaPlaylist(QObject *parent)
    : QObject(parent)
    , d_ptr(new QMediaPlaylistPrivate)
{
    Q_D(QMediaPlaylist);

    d->q_ptr = this;
}


QMediaPlaylist::~QMediaPlaylist()
{
    delete d_ptr;
}

/*!
  \property QMediaPlaylist::playbackMode

  This property defines the order that items in the playlist are played.

  \sa QMediaPlaylist::PlaybackMode
*/

QMediaPlaylist::PlaybackMode QMediaPlaylist::playbackMode() const
{
    return d_func()->playbackMode;
}

void QMediaPlaylist::setPlaybackMode(QMediaPlaylist::PlaybackMode mode)//设置播放模式
{
    Q_D(QMediaPlaylist);

    if (mode == d->playbackMode)
        return;

    d->playbackMode = mode;

    emit playbackModeChanged(mode);
}


int QMediaPlaylist::currentIndex() const//当前播放文件在列表中位置
{
    return d_func()->currentPos;
}



QUrl QMediaPlaylist::currentMedia() const//当前播放的媒体文件，返回QUrl
{
    Q_D(const QMediaPlaylist);
    if (d->currentPos < 0 || d->currentPos >= d->playlist.size())
        return QUrl();
    return d_func()->playlist.at(d_func()->currentPos);
}


int QMediaPlaylist::nextIndex(int steps) const//steps步后将播放的歌在播放列表中索引
{
    return d_func()->nextPosition(steps);
}


int QMediaPlaylist::previousIndex(int steps) const//steps步前应该播放的歌在播放列表中索引
{
    return d_func()->prevPosition(steps);
}


int QMediaPlaylist::mediaCount() const//列表中所有文件数
{
    return d_func()->playlist.count();
}


bool QMediaPlaylist::isEmpty() const//列表是否为空？
{
    return mediaCount() == 0;
}


QUrl QMediaPlaylist::media(int index) const//返回特定index对应的媒体文件的QUrl
{
    Q_D(const QMediaPlaylist);
    if (index < 0 || index >= d->playlist.size())
        return QUrl();
    return d->playlist.at(index);
}

void QMediaPlaylist::addMedia(const QUrl &content)//向列表中添加单个歌曲
{
    Q_D(QMediaPlaylist);
    int pos = d->playlist.size();
    emit mediaAboutToBeInserted(pos, pos);
    d->playlist.append(content);
    emit mediaInserted(pos, pos);
}

/*!
  Append multiple media content \a items to the playlist.

  Returns true if the operation is successful, otherwise returns false.
  */
void QMediaPlaylist::addMedia(const QList<QUrl> &items)//向列表中添加多个媒体文件
{
    if (!items.size())
        return;

    Q_D(QMediaPlaylist);
    int first = d->playlist.size();
    int last = first + items.size() - 1;
    emit mediaAboutToBeInserted(first, last);
    d_func()->playlist.append(items);
    emit mediaInserted(first, last);//插入位置，从first到last
}


bool QMediaPlaylist::insertMedia(int pos, const QUrl &content)//在指定位置插入单曲
{
    Q_D(QMediaPlaylist);
    pos = qBound(0, pos, d->playlist.size());
    emit mediaAboutToBeInserted(pos, pos);
    d->playlist.insert(pos, content);
    emit mediaInserted(pos, pos);
    return true;
}


bool QMediaPlaylist::insertMedia(int pos, const QList<QUrl> &items)//插入多个单曲（指定起始位置）
{
    if (!items.size())
        return true;

    Q_D(QMediaPlaylist);
    pos = qBound(0, pos, d->playlist.size());
    int last = pos + items.size() - 1;
    emit mediaAboutToBeInserted(pos, last);
    auto newList = d->playlist.mid(0, pos);
    newList += items;
    newList += d->playlist.mid(pos);
    d->playlist = newList;
    emit mediaInserted(pos, last);
    return true;
}


bool QMediaPlaylist::moveMedia(int from, int to)//移动媒体文件
{
    Q_D(QMediaPlaylist);
    if (from < 0 || from > d->playlist.count() ||
        to < 0 || to > d->playlist.count())
        return false;

    d->playlist.move(from, to);
    emit mediaChanged(from, to);
    return true;
}

bool QMediaPlaylist::removeMedia(int pos)//删除指定位置媒体文件
{
    return removeMedia(pos, pos);
}

bool QMediaPlaylist::removeMedia(int start, int end)//删除一系列媒体文件
{
    Q_D(QMediaPlaylist);
    if (end < start || end < 0 || start >= d->playlist.count())
        return false;
    start = qBound(0, start, d->playlist.size() - 1);
    end = qBound(0, end, d->playlist.size() - 1);

    emit mediaAboutToBeRemoved(start, end);
    d->playlist.remove(start, end - start + 1);
    emit mediaRemoved(start, end);
    return true;
}

void QMediaPlaylist::clear()//清除列表中所有媒体文件
{
    Q_D(QMediaPlaylist);
    int size = d->playlist.size();
    emit mediaAboutToBeRemoved(0, size - 1);
    d->playlist.clear();
    emit mediaRemoved(0, size - 1);
}

void QMediaPlaylist::load(const QUrl &location, const char *format)//加载播放列表
{
    Q_D(QMediaPlaylist);

    d->error = NoError;
    d->errorString.clear();

    d->ensureParser();
    d->parser->start(location, QString::fromUtf8(format));
}


void QMediaPlaylist::load(QIODevice *device, const char *format)
{
    Q_D(QMediaPlaylist);

    d->error = NoError;
    d->errorString.clear();

    d->ensureParser();
    d->parser->start(device, QString::fromUtf8(format));
}

bool QMediaPlaylist::save(const QUrl &location, const char *format) const//保存播放列表到指定位置
{
    Q_D(const QMediaPlaylist);

    d->error = NoError;
    d->errorString.clear();

    if (!d->checkFormat(format))
        return false;

    QFile file(location.toLocalFile());

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        d->error = AccessDeniedError;
        d->errorString = tr("The file could not be accessed.");
        return false;
    }

    return save(&file, format);
}


bool QMediaPlaylist::save(QIODevice *device, const char *format) const
{
    Q_D(const QMediaPlaylist);

    d->error = NoError;
    d->errorString.clear();

    if (!d->checkFormat(format))
        return false;

    QM3uPlaylistWriter writer(device);
    for (const auto &entry : d->playlist)
        writer.writeItem(entry);
    return true;
}


QMediaPlaylist::Error QMediaPlaylist::error() const//返回错误类型
{
    return d_func()->error;
}


QString QMediaPlaylist::errorString() const//返回错误类型
{
    return d_func()->errorString;
}


void QMediaPlaylist::shuffle()//重新排序列表
{
    Q_D(QMediaPlaylist);
    QList<QUrl> playlist;

    // 当前播放内容不变
    QUrl current;
    if (d->currentPos != -1)
        current = d->playlist.takeAt(d->currentPos);

    while (!d->playlist.isEmpty())//随机排序
        playlist.append(d->playlist.takeAt(QRandomGenerator::global()->bounded(int(d->playlist.size()))));

    if (d->currentPos != -1)
        playlist.insert(d->currentPos, current);
    d->playlist = playlist;
    emit mediaChanged(0, d->playlist.count());
}


void QMediaPlaylist::next()//下一首音乐
{
    Q_D(QMediaPlaylist);
    d->currentPos = d->nextPosition(1);

    emit currentIndexChanged(d->currentPos);
    emit currentMediaChanged(currentMedia());
}


void QMediaPlaylist::previous()//前一首音乐
{
    Q_D(QMediaPlaylist);
    d->currentPos = d->prevPosition(1);

    emit currentIndexChanged(d->currentPos);
    emit currentMediaChanged(currentMedia());
}

void QMediaPlaylist::setCurrentIndex(int playlistPosition)//当前播放歌曲的index
{
    Q_D(QMediaPlaylist);
    if (playlistPosition < 0 || playlistPosition >= d->playlist.size())
        playlistPosition = -1;
    d->currentPos = playlistPosition;

    emit currentIndexChanged(d->currentPos);
    emit currentMediaChanged(currentMedia());
}

/*!
    \fn void QMediaPlaylist::mediaInserted(int start, int end)

    This signal is emitted after media has been inserted into the playlist.
    The new items are those between \a start and \a end inclusive.
 */

/*!
    \fn void QMediaPlaylist::mediaRemoved(int start, int end)

    This signal is emitted after media has been removed from the playlist.
    The removed items are those between \a start and \a end inclusive.
 */

/*!
    \fn void QMediaPlaylist::mediaChanged(int start, int end)

    This signal is emitted after media has been changed in the playlist
    between \a start and \a end positions inclusive.
 */

/*!
    \fn void QMediaPlaylist::currentIndexChanged(int position)

    Signal emitted when playlist position changed to \a position.
*/

/*!
    \fn void QMediaPlaylist::playbackModeChanged(QMediaPlaylist::PlaybackMode mode)

    Signal emitted when playback mode changed to \a mode.
*/

/*!
    \fn void QMediaPlaylist::mediaAboutToBeInserted(int start, int end)

    Signal emitted when items are to be inserted at \a start and ending at \a end.
*/

/*!
    \fn void QMediaPlaylist::mediaAboutToBeRemoved(int start, int end)

    Signal emitted when item are to be deleted at \a start and ending at \a end.
*/

/*!
    \fn void QMediaPlaylist::currentMediaChanged(const QUrl &content)

    Signal emitted when current media changes to \a content.
*/

/*!
    \property QMediaPlaylist::currentIndex
    \brief Current position.
*/

/*!
    \property QMediaPlaylist::currentMedia
    \brief Current media content.
*/

/*!
    \fn QMediaPlaylist::loaded()

    Signal emitted when playlist finished loading.
*/

/*!
    \fn QMediaPlaylist::loadFailed()

    Signal emitted if failed to load playlist.
*/

/*!
    \enum QMediaPlaylist::Error

    This enum describes the QMediaPlaylist error codes.

    \value NoError                 No errors.
    \value FormatError             Format error.
    \value FormatNotSupportedError Format not supported.
    \value NetworkError            Network error.
    \value AccessDeniedError       Access denied error.
*/

QT_END_NAMESPACE

//#include "moc_qmediaplaylist.cpp"
