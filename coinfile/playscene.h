#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelnum);

    int leveldex;
    void paintEvent(QPaintEvent *);
    int startarry[4][4];

    Mycoin * coinbtn[4][4];
    //是否胜利
    bool iswin;

signals:
        void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
