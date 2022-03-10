#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QString>
#include <QPainter>
#include "mypushbutton.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include "mycoin.h"
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelnum)
{
    QString str=QString("你进入了第 %1 关 ").arg(levelnum);
    qDebug()<<str;
    this->leveldex=levelnum;

    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("游戏场景");
    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QString kaishi="开始1";
    QString tuichu="退出1";
    //创建开始菜单
    QMenu * startMenu = bar->addMenu(kaishi);

    //创建退出 菜单项

    QAction *  quitAction = startMenu->addAction(tuichu);

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width() , this->height() - backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug() << "翻金币场景中：点击了返回按钮";
        backSound->play();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });
    //显示关卡
    QLabel *label= new QLabel;
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(20);
    label->setFont(font);
    label->setParent(this);
    label->setGeometry(30,this->height()-50,120,50);
    QString str1= QString("Level %1").arg(levelnum);
    label->setText(str1);
    //胜利图片显示
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            startarry[i][j]=config.mData[leveldex][i][j];
        }
    }
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    //金币背景
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //绘制背景图片
           QPixmap pix= QPixmap(":/res/BoardNode(1).png");
            QLabel* label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*50,200+j*50);
            QString str2;
            if(this->startarry[i][j]==1)
            {
               str2=":/res/Coin0001.png";

            }
            else
            {
                str2=":/res/Coin0008.png";
            }
            Mycoin *coin = new Mycoin(str2);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->startarry[i][j];
            coinbtn[i][j]=coin;


            connect(coin,&Mycoin::clicked,[=](){
                flipSound->play();
                coin->changeFlag();
                this->startarry[i][j]=this->startarry[i][j]==0? 1:0;
                //翻转周围金币

                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinbtn[coin->posX+1][coin->posY]->changeFlag();
                        this->startarry[coin->posX+1][coin->posY]=this->startarry[coin->posX+1][coin->posY]==0? 1:0;
                    }
                    //左侧
                    if(coin->posX-1>=0)
                    {
                        coinbtn[coin->posX-1][coin->posY]->changeFlag();
                        this->startarry[coin->posX-1][coin->posY]=this->startarry[coin->posX-1][coin->posY]==0? 1:0;
                    }
                    //xia侧
                    if(coin->posY+1<=3)
                    {
                        coinbtn[coin->posX][coin->posY+1]->changeFlag();
                        this->startarry[coin->posX][coin->posY+1]=this->startarry[coin->posX][coin->posY+1]==0? 1:0;
                    }
                    //shang侧
                    if(coin->posY-1>=0)
                    {
                        coinbtn[coin->posX][coin->posY-1]->changeFlag();
                        this->startarry[coin->posX][coin->posY-1]=this->startarry[coin->posX][coin->posY-1]==0? 1:0;
                    }


                    //判断是否胜利
                    this->iswin = true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {
                                this->iswin = false;
                                break;
                            }

                        }
                    }
                    if(this->iswin == true)
                    {
                        qDebug()<<"游戏胜利";
                        winSound->play();
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinbtn[i][j]->iswin=true;

                            }
                        }
                        //将胜利的图片移动下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);

                        //设置开始位置
                        animation->setStartValue(QRect(QPoint(winLabel->x(),winLabel->y()),QPoint(winLabel->x()+winLabel->width(),winLabel->height())));
                        //设置结束位置
                        animation->setEndValue(QRect(QPoint(winLabel->x(),winLabel->y()+120),QPoint(winLabel->x()+winLabel->width(),winLabel->height()+120)));

                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                    //





                });

            });

        }
    }




}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //绘制背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制标题
    pix.load(":/res/Title.png");
    pix=pix.scaled( pix.width() * 0.5 , pix.height() * 0.5);//缩放
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
