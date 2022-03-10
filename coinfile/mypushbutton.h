#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QString>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);防止隐式类型转换
    MyPushButton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressedImgPath;

    void zoom1();
    void zoom2();


    //重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
