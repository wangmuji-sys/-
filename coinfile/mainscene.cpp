#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QPainter>
#include "mypushbutton.h"
#include <QPushButton>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置窗口属性
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    connect(ui->quit,&QAction::triggered,[=](){
        this->close();
    });
    MyPushButton * startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);

    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5 ,this->height() * 0.7);
    QSound* startSound=new QSound(":/res/BackButtonSound.wav",this);
    ChooseLevelScene * chooseScence= new ChooseLevelScene;
    connect(chooseScence,&ChooseLevelScene::chooseSenceback,this,[=](){

        this->setGeometry(chooseScence->geometry());
        chooseScence->hide();
        this->show();

    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            chooseScence->setGeometry(this->geometry());
            startSound->play();
            this->hide();
            chooseScence->show();


        });
    });


}
void MainScene::paintEvent(QPaintEvent *)
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
MainScene::~MainScene()
{
    delete ui;
}
