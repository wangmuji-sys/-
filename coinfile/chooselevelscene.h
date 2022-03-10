#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    PlayScene *play= NULL;

signals:
    //自定义信号告诉主程序返回
    void chooseSenceback();


public slots:
};

#endif // CHOOSELEVELSCENE_H
