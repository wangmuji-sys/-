#include "chooselevelscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QMenuBar>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QString>
#include "playscene.h"
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    QString kaishi="开始 ";
    QString tuichu="退出 ";
    //创建开始菜单
    QMenu * startMenu = bar->addMenu(kaishi);

    //创建退出 菜单项

    QAction *  quitAction = startMenu->addAction(tuichu);

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    MyPushButton * chooseBtn =new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    chooseBtn->setParent(this);
    chooseBtn->move(this->width()-chooseBtn->width(),this->height()-chooseBtn->height());
    connect(chooseBtn,&MyPushButton::clicked,[=](){
        QTimer::singleShot(500,this,[=](){
            backSound->play();

//            qDebug()<<" 点击了返回 ";
            emit this->chooseSenceback();
    });


    });
     QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //创建选择关的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn= new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4*70),130+(i/4*70));
        //监听按钮信号
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str=QString("你选择了第 %1 关 ").arg(i+1);
            qDebug()<<str;
            chooseSound->play();

            this->hide();
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play= NULL;
            });

        });

        QLabel *lable1=new QLabel;
        lable1->setParent(this);
        lable1->setFixedSize(menuBtn->width(),menuBtn->height());
        lable1->setText(QString::number(i+1));
        lable1->move(25+(i%4*70),130+(i/4*70));
        lable1->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);

        lable1->setAttribute(Qt::WA_TransparentForMouseEvents);
    }



}
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //绘制背景
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制标题
    pix.load(":/res/Title.png");
//    pix=pix.scaled( pix.width() * 0.5 , pix.height() * 0.5);//缩放
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
