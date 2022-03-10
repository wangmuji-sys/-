#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class Mycoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit Mycoin(QWidget *parent = nullptr);
    Mycoin(QString coinimg);
    int posX;//x 坐标
    int posY;//y 坐标
    bool flag;// 正反提示

    void changeFlag();
    QTimer * timer1;
    QTimer * timer2;
    int min =1;
    int max =8;
    //执行动画的标志
    bool isAnimation=false;
    //捕捉按下和释放
    void mousePressEvent(QMouseEvent *e);
    //是否胜利
    bool iswin = false;

signals:

public slots:
};

#endif // MYCOIN_H
