#include "mycoin.h"
#include <QDebug>
#include <QTimer>
//Mycoin::Mycoin(QWidget *parent) : QPushButton(parent)
//{

//}
 Mycoin::Mycoin(QString coinimg)
 {
     QPixmap pixmap;
     bool ret = pixmap.load(coinimg);
     if(!ret)
     {
         QString str = QString("图片 %1 加载失败 ").arg(coinimg);
         qDebug()<<str;
     }
     this->setFixedSize(pixmap.width(),pixmap.height());
     this->setStyleSheet("QPushButtonm{border:0px}");
     this->setIcon(pixmap);
     this->setIconSize(QSize(pixmap.width(),pixmap.height()));

     timer1 = new QTimer(this);
     timer2 = new QTimer(this);
     //监听翻金币信号
     connect(timer1,&QTimer::timeout,[=](){
         QPixmap pix;
         QString str=QString(":/res/Coin000%1.png").arg(this->min++);
         pix.load(str);
         this->setFixedSize(pix.width(),pix.height());
         this->setStyleSheet("QPushButtonm{border:0px}");
         this->setIcon(pix);
         this->setIconSize(QSize(pix.width(),pix.height()));
         if(this->min>this->max)
         {
             this->min=1;
             isAnimation=false;
             timer1->stop();
         }

     });
     connect(timer2,&QTimer::timeout,[=](){
         QPixmap pix;
         QString str=QString(":/res/Coin000%1.png").arg(this->max--);
         pix.load(str);
         this->setFixedSize(pix.width(),pix.height());
         this->setStyleSheet("QPushButtonm{border:0px}");
         this->setIcon(pix);
         this->setIconSize(QSize(pix.width(),pix.height()));
         if(this->max<this->min)
         {
             this->max=8;
             isAnimation=false;
             timer2->stop();
         }

     });
     
 }
void  Mycoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isAnimation=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        isAnimation=true;
        this->flag=true;
    }

}
void Mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->iswin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
