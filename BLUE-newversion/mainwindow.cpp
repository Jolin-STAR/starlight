#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QAbstractItemModel"
#include <QtCore/qlist.h>
#include <QtCore/qfile.h>
#include <QtCore/qurl.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qcoreapplication.h>
#include "qaudiooutput.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(tracksChanged()));
        timer->start(2000);

    ui->setupUi(this);

//UI设计
       { //设置主界面背景
        {QPixmap pixmap(":/images/Resource/images/background.jpg");
        QPalette palette;
        palette.setBrush(backgroundRole(),QBrush(pixmap));
        setPalette(palette);}
        //设置窗口标题与图案
        this->setWindowTitle("蓝色布谷鸟Player");
        this->setWindowIcon(QIcon(":/images/Resource/images/bluebird-ico.ico"));
        //播放按钮ui设计
       { ui->prebtn->setToolTip("上一首");
            ui->prebtn->setAutoRaise(true);
            ui->prebtn->setIcon(QPixmap(":/images/Resource/images/preone.png"));
            ui->prebtn->setIconSize(QSize(72,72));
        ui->playbtn->setToolTip("暂停");
            ui->playbtn->setAutoRaise(true);
            ui->playbtn->setIcon(QPixmap(":/images/Resource/images/pause.png"));
            ui->playbtn->setIconSize(QSize(72,72));
//            ui->playbtn->setStyleSheet("\
//                    QToolButton:hover{border-image:  url(:/images/Resource/images/history.png);}\
//                    QToolButton:pressed{border-image:  url(:/images/Resource/images/history.png);}");
          ui->nextbtn->setAutoRaise(true);
            ui->nextbtn->setIcon(QPixmap(":/images/Resource/images/nextone.png"));
            ui->nextbtn->setIconSize(QSize(72,72));
        ui->fullscreenbtn->setToolTip("全屏");
            ui->fullscreenbtn->setAutoRaise(true);
            ui->fullscreenbtn->setIcon(QPixmap(":/images/Resource/images/fullscreen.png"));
            ui->fullscreenbtn->setIconSize(QSize(72,72));
        ui->volumebtn->setToolTip("音量");
            ui->volumebtn->setAutoRaise(true);
            ui->volumebtn->setIconSize(QSize(72,72));
            ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/voice.png"));     
       ui->openfilebtn->setToolTip("打开文件");
            ui->openfilebtn->setAutoRaise(true);
            ui->openfilebtn->setIcon(QPixmap(":/images/Resource/images/openfile.png"));
       ui->PlayMode->setToolTip("只播放当前");
            ui->PlayMode->setAutoRaise(true);
            ui->PlayMode->setIcon(QPixmap(":/images/Resource/images/curentonce.png"));
            ui->PlayMode->setIconSize(QSize(72,72));
       ui->openfilebtn->setToolTip("播放倍速");
            ui->ratebtn->setIcon(QPixmap(":/images/Resource/images/1.0playrate.png"));
            ui->ratebtn->setIconSize(QSize(72,72));

     //列表项ui
     {


            }
     }
     //标签ui设计
        {   QFont ft;
            ft.setPointSize(30);
            QPalette pa;
            pa.setColor(QPalette::WindowText,QColor("#565d6f"));

           ui->sumtime->setPalette(pa);
                ui->sumtime->setFont(ft);
                ui->sumtime->setText("00:00:00");
           ui->passedtime->setPalette(pa);
                ui->passedtime->setFont(ft);
                ui->passedtime->setText("00:00:00");

        }
     //滑动条ui设计
        {
        //滑动的按键
        ui->progressbar->setStyleSheet(
            "QSlider::handle:horizontal{            border: 0px ;/"
            " border-image:  url(:/images/Resource/images/history.png);/"
            "width: 15px;                                           /"
            "margin: -7px -7px -7px -7px;  }");
        //没有滑上去的地方
        ui->progressbar->setStyleSheet(
            "QSlider::add-page:horizontal{ spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, 	stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc  }");
        //滑过的地方
        ui->progressbar->setStyleSheet(
            "QSlider::sub-page：horizontal{ background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, 	stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);   }");

//        /* 设置中间的那个滑动的键 */
//        QSlider::handle:horizontal {
//        border: 0px ;
//        border-image:  url(:/NiceTalk/Images/Setting/volume_nor.png);
//        width: 15px;
//        margin: -7px -7px -7px -7px;
//        }
//        /* 还没有滑上去的地方 */
//        QSlider::add-page:horizontal{
//        background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, 	stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);
//        }
//        /* 已经划过的从地方 */
//        QSlider::sub-page:horizontal{
//        background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, 	stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);
//        }


}



    }

//播放器与播放区域对象
   { vedioWidget=new QVideoWidget(ui->playarea);
        vedioWidget->resize(ui->playarea->size());

    mediaPlayer=new QMediaPlayer(this);
    audioOutput=new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setVideoOutput(vedioWidget);//播放区域

    //滑动音轨最大最小及步长设置
    {
    ui->volslider->setMinimum(0);
    ui->volslider->setMaximum(100);
    ui->volslider->setSingleStep(2);
    }

    //初始时按钮禁用
    {
        ui->playbtn->setDisabled(1);
        ui->prebtn->setDisabled(1);
        ui->nextbtn->setDisabled(1);
        ui->PlayMode->setDisabled(1);
        ui->progressbar->setDisabled(1);
        ui->volumebtn->setDisabled(1);
        ui->volslider->setDisabled(1);
        ui->ratebtn->setDisabled(1);
        ui->fullscreenbtn->setDisabled(1);
    }

    }

//connect音轨变化槽函数
    connect(ui->volslider, &QSlider::sliderMoved,this, &MainWindow::setVolume);
    connect(ui->volslider, &QSlider::valueChanged,this, &MainWindow::setVolume);
//connect时间标签变化槽函数
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)), this, SLOT(setduration(qint64)));
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)), this, SLOT(setpassedtime(qint64)));    
//connect视频轨道槽函数
    //若监听player播放状态改变，则执行改变播放图标函数
    connect(mediaPlayer,SIGNAL(stateChanged(QmediaPlayer::PlaybackState)),this,SLOT(mediaStateChanged(QMediaPlayer::PlaybackState state)));
    //播放进度变化函数
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    //播放长度信号变化
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));





    {
    if(QMediaPlayer::EndOfMedia)
        emit EndOfMedia();

//播放列表设置
    m_playlistModel = new PlaylistModel(this);
    m_playlist = m_playlistModel->playlist();
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::playlistPositionChanged);

#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
    ui->m_playlistView->setModel(m_playlistModel);
    ui->m_playlistView->setCurrentIndex(m_playlistModel->index(m_playlist->currentIndex(), 0));
    connect(ui->m_playlistView, &QAbstractItemView::activated, this, &MainWindow::jump);
#endif

}


    //鼠标追踪
   {
        ui->centralwidget->setMouseTracking(true);  //设为移动监视
        this->setMouseTracking(true);
        QTimer *timer = new QTimer(this);  //计时器
        connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));//连接信号
        timer->start(5000);//每五秒触发一次
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

//调节音量槽函数
void MainWindow::setVolume(int position){


    //滑动时更改对应播音图标
    {   int volvalue=ui->volslider->value();
        if(volvalue>=60){
            ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/voice.png"));
        }else if(volvalue>1){
             ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/lowvoice.png"));
        }else if(volvalue<1){
            ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/silence.png"));
        }
    }


    qreal linearVolume = QAudio::convertVolume(position/qreal(100.0),
                                                    QAudio::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    audioOutput->setVolume(linearVolume);



 }


bool MainWindow::isPlayerAvailable() const
{
    return mediaPlayer->isAvailable();
}

//点击打开文件槽函数
void MainWindow::on_openfilebtn_clicked()
{
    open();
}

//点击播放槽函数
void MainWindow::on_playbtn_clicked()
{
    play();//若处于播放，则停止，若停止，则播放
}
    void MainWindow::play()
{//play函数根据当前的播放窗台来分别执行暂停或播放
    switch(mediaPlayer->playbackState())
    {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        ui->playbtn->setIcon(QPixmap(":/images/Resource/images/play2.png"));
        break;
    case QMediaPlayer::PausedState:
        mediaPlayer->play();
        ui->playbtn->setIcon(QPixmap(":/images/Resource/images/pause.png"));
        break;
    default:
        mediaPlayer->play();
        ui->playbtn->setIcon(QPixmap(":/images/Resource/images/pause.png"));
        break;
    }
}
    static bool isPlaylist(const QUrl &url) // 是否是“.m3u”格式的播放列表？
    {
        if (!url.isLocalFile())//若该播放列表不是本地文件
            return false;
        const QFileInfo fileInfo(url.toLocalFile());//文件信息
        return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);//该列表是本地文件，格式符合
    }

    void MainWindow::addToPlaylist(const QList<QUrl> &urls)
    {
        const int previousMediaCount = m_playlist->mediaCount();
        int sign=0;
        if(!m_playlist->isEmpty())//播放列表不为空，列表中加入单曲后也不切歌
            sign=1;
        for (auto &url: urls) {
            if (isPlaylist(url))
                m_playlist->load(url);
            else
                m_playlist->addMedia(url);
        }
        if (m_playlist->mediaCount() > previousMediaCount&&sign==0) {
            auto index = m_playlistModel->index(previousMediaCount, 0);
            if (ui->m_playlistView)
                    ui->m_playlistView->setCurrentIndex(index);
            jump(index);
            mediaPlayer->play();//播放列表初始为空，直接播第一首歌
        }
    }
    void MainWindow::open()
    {
        QFileDialog fileDialog(this);
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
        fileDialog.setWindowTitle(tr("打开文件"));
        fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
        if (fileDialog.exec() == QDialog::Accepted)
            addToPlaylist(fileDialog.selectedUrls());
        //成功加入文件后，启用/恢复按钮使用图标
        {
            ui->playbtn->setDisabled(0);
            ui->prebtn->setDisabled(0);
            ui->nextbtn->setDisabled(0);
            ui->PlayMode->setDisabled(0);
            ui->progressbar->setDisabled(0);
            ui->volumebtn->setDisabled(0);
            ui->volslider->setDisabled(0);
            ui->ratebtn->setDisabled(0);
            ui->fullscreenbtn->setDisabled(0);
        }

        audioOutput->setVolume(0.3);
        ui->volslider->setValue(30);

    }

//时间标签槽函数
    void MainWindow::setduration(qint64 dur)
    {
        ui->progressbar->setRange(0,dur);
        QTime time=QTime(0,0,0).addMSecs(dur);
        QString sum=time.toString("HH:mm:ss");
        ui->sumtime->setText(sum);


    }
    void MainWindow::setpassedtime(qint64 passedtime)
    {
         QTime time=QTime(0,0,0).addMSecs(passedtime);
         QString pass=time.toString("HH:mm:ss");
         ui->passedtime->setText(pass);

    }


//上一首按钮槽函数
void MainWindow::on_prebtn_clicked()
{
    if (mediaPlayer->position() <= 5000) {
        m_playlist->previous();
    } else {
        mediaPlayer->setPosition(0);
    }
    mediaPlayer->play();
}
//下一首按钮槽函数
void MainWindow::on_nextbtn_clicked()
{
    m_playlist->next();
    mediaPlayer->play();
}
//播放快进槽函数
void MainWindow::on_ratebtn_clicked()
    {
        if(mediaPlayer->playbackRate()==0.5){
            mediaPlayer->setPlaybackRate(1);
            ui->ratebtn->setIcon(QPixmap(":/images/Resource/images/1.0playrate.png"));
        }else if(mediaPlayer->playbackRate()==1){
            mediaPlayer->setPlaybackRate(1.5);
            ui->ratebtn->setIcon(QPixmap(":/images/Resource/images/1.5playrate.png"));
        }else if(mediaPlayer->playbackRate()==1.5){
            mediaPlayer->setPlaybackRate(2);
            ui->ratebtn->setIcon(QPixmap(":/images/Resource/images/2playrate.png"));
        }
        else if (mediaPlayer->playbackRate()==2){
            mediaPlayer->setPlaybackRate(0.5);
            ui->ratebtn->setIcon(QPixmap(":/images/Resource/images/0.5rate.png"));
        }
    }


//开静音按钮槽函数
void MainWindow::on_volumebtn_clicked()
{   int s=ui->volslider->value();
    if (s==0) {
   //当前是静音状态
       ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/voice.png"));
       ui->volumebtn->setToolTip("播放");
        ui->volslider->setValue(30);

     }
   //当前不是静音状态
   else{
        ui->volumebtn->setIcon(QPixmap(":/images/Resource/images/silence.png"));
        ui->volumebtn->setToolTip("静音");
        ui->volslider->setValue(0);
      }
}
//播放模式改变
void MainWindow::on_PlayMode_clicked()
{

    switch(m_playlist->playbackMode())
    {
    case QMediaPlaylist::CurrentItemInLoop://当前单曲循环
        m_playlist->setPlaybackMode(QMediaPlaylist::Random);//切换为随机播放模式
        ui->PlayMode->setToolTip("随机播放");
        ui->PlayMode->setIcon(QPixmap(":/images/Resource/images/random.png"));
        break;
    case QMediaPlaylist::Random://当前随机播放
        m_playlist->setPlaybackMode(QMediaPlaylist::Loop);//切换为列表循环
        ui->PlayMode->setToolTip("列表循环");
        ui->PlayMode->setIcon(QPixmap(":/images/Resource/images/loop.png"));
        break;
    case QMediaPlaylist::Loop://当前列表顺序循环
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);//切换为只播放当前
        ui->PlayMode->setToolTip("只播放当前");
        ui->PlayMode->setIcon(QPixmap(":/images/Resource/images/curentonce.png"));
        break;
    case QMediaPlaylist::CurrentItemOnce://当前为只播放该单曲一次
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);//切换为单曲循环
        ui->PlayMode->setToolTip("单曲循环");
        ui->PlayMode->setIcon(QPixmap(":/images/Resource/images/singleloop.png"));
        break;

    }
}
void MainWindow::tracksChanged()
{
    switch(mediaPlayer->mediaStatus())
    {
    case QMediaPlayer::EndOfMedia:
    {
        m_playlist->next();
        mediaPlayer->play();
        break;
    }
    default:
        return;

    }
}






//播放函数的辅助函数
        //改变播放图标槽函数
        void MainWindow::mediaStateChanged(QMediaPlayer::PlaybackState state)
         {
             //播放与暂停的图标效果
             switch (state) {
             case QMediaPlayer::PlayingState:
                 ui->playbtn->setIcon(QPixmap(":/images/Resource/images/play2.png"));
                 ui->playbtn->setToolTip("暂停");
                 break;
             default:
                 ui->playbtn->setIcon(QPixmap(":/images/Resource/images/pause.png"));
                 ui->playbtn->setToolTip("播放");
                 break;
             }
         }
         //改变位置槽函数
         void MainWindow::positionChanged(qint64 position){
             //进度条点改变
             ui->progressbar->setValue(position);
         }
         void MainWindow::durationChanged(qint64 duration){
             ui->progressbar->setRange(0,duration);
         }
         void MainWindow::setPosition(int position)
         {
             mediaPlayer->setPosition(position);
         }
         //播放进度条滑动槽函数
          void MainWindow::on_progressbar_sliderMoved(int position)
    {
        mediaPlayer->setPosition(position);
    }


//重写键盘事件
//设置音量快捷键
    void MainWindow::keyPressEvent(QKeyEvent* event)
    {
        //增大声音
        if(event->modifiers()& Qt::ControlModifier){
           if(event->key()==Qt::Key_Up){
            int currentvol=ui->volslider->value();
            int newvol=currentvol+1;
           // ui->volumebtn->setIcon(QIcon(":/images/Resource/images/increasevol.png"));
            ui->volslider->setValue(newvol);
            }
        }
        //减小声音
        else if(event->modifiers()& Qt::ControlModifier){
               if(event->key()==Qt::Key_Down){
                   int currentvol=ui->volslider->value();
                   int newvol=currentvol-1;
                  //  ui->volumebtn->setIcon(QIcon(":/images/Resource/images/decreasevol.png"));
                   ui->volslider->setValue(newvol);
               }
        }

    }


//重写绘图事件
//播放窗口自适应设置
    void MainWindow::paintEvent(QPaintEvent *event)
    {
        vedioWidget->resize(ui->playarea->size());
    }


//重写鼠标事件
//全屏显示--ui槽
    void MainWindow::on_fullscreenbtn_clicked()
    {
        //判断窗口状态
        if(isFullScreen()){
            ui->fullscreenbtn->setToolTip("大屏播放");
            ui->fullscreenbtn->setIcon(QPixmap(":/images/Resource/images/fullscreen.png"));

            showNormal();
            ui->downwindow->setVisible(true);
            ui->widget_2->setVisible(true);
            ui->m_playlistView->setVisible(true);
            ui->statusbar->setVisible(true);

            ui->downspacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);
           // ui->leftSpacer->changeSize(20, 20, QSizePolicy::Expanding);
            ui->middleSpacer->changeSize(20, 5, QSizePolicy::Preferred, QSizePolicy::Expanding);
            //ui->rightSpacer->changeSize(20, 20, QSizePolicy::Expanding);
            ui->upperSpacer->changeSize(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding);
            ui->verticalSpacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);

            ui->playdownSpacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);
            ui->playmiddleSpacer->changeSize(20, 20, QSizePolicy::Expanding);
            ui->playupperSpacer->changeSize(20, 13, QSizePolicy::Preferred, QSizePolicy::Expanding);

        }else{
            ui->fullscreenbtn->setToolTip("小屏播放");
            ui->fullscreenbtn->setIcon(QPixmap(":/images/Resource/images/littlescreen.png"));

            showFullScreen();
            ui->downwindow->setVisible(false);
            ui->widget_2->setVisible(false);
            ui->m_playlistView->setVisible(false);
            ui->statusbar->setVisible(false);

            ui->downspacer->changeSize(0,0);

            ui->middleSpacer->changeSize(0,0);

            ui->upperSpacer->changeSize(0,0);
            ui->verticalSpacer->changeSize(0,0);

            ui->playdownSpacer->changeSize(0,0);
            ui->playmiddleSpacer->changeSize(0,0);
            ui->playupperSpacer->changeSize(0,0);

        }
    }

   //鼠标事件重写
    void MainWindow::mouseMoveEvent(QMouseEvent *event)
    {
        setCursor(Qt::ArrowCursor);  //显示鼠标
        ui->downwindow->setVisible(true);
        ui->widget_2->setVisible(true);
        ui->m_playlistView->setVisible(true);
        ui->statusbar->setVisible(true);

        ui->downspacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);
        //ui->leftSpacer->changeSize(20, 20, QSizePolicy::Expanding);
        ui->middleSpacer->changeSize(20, 5, QSizePolicy::Preferred, QSizePolicy::Expanding);
       // ui->rightSpacer->changeSize(20, 20, QSizePolicy::Expanding);
        ui->upperSpacer->changeSize(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding);
        ui->verticalSpacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);

        ui->playdownSpacer->changeSize(20, 10, QSizePolicy::Preferred, QSizePolicy::Expanding);
        ui->playmiddleSpacer->changeSize(20, 20, QSizePolicy::Expanding);
        ui->playupperSpacer->changeSize(20, 13, QSizePolicy::Preferred, QSizePolicy::Expanding);
    }

    //鼠标没移动五秒调用
    void MainWindow::timerUpdate()
    {
        if(isFullScreen()){
        this->setCursor(Qt::BlankCursor);  //隐藏鼠标

        ui->downwindow->setVisible(false);
        ui->widget_2->setVisible(false);
        ui->m_playlistView->setVisible(false);
        ui->statusbar->setVisible(false);

        ui->downspacer->changeSize(0,0);
       // ui->leftSpacer->changeSize(0,0);
        ui->middleSpacer->changeSize(0,0);
       // ui->rightSpacer->changeSize(0,0);
        ui->upperSpacer->changeSize(0,0);
        ui->verticalSpacer->changeSize(0,0);

        ui->playdownSpacer->changeSize(0,0);
        ui->playmiddleSpacer->changeSize(0,0);
        ui->playupperSpacer->changeSize(0,0);
}
    }


