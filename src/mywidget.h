#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QtGui>

namespace Ui
{
    class Form;
}

class MyWidget : public QWidget
{
    Q_OBJECT

    Ui::Form *ui;
    int variant;

    qreal f(qreal x, qreal y, qreal z);
    qreal g(qreal x, qreal y, qreal z);
    qreal x0();
    qreal y0();
    qreal z0();
    qreal xFinish();
    qreal h();
    qreal yt(qreal x);
    qreal ypo(qreal y, qreal x);

    qreal f5(qreal x, qreal y, qreal z);
    qreal g5(qreal x, qreal y, qreal z);
    qreal x05();
    qreal y05();
    qreal z05();
    qreal xFinish5();
    qreal h5();
    qreal yt5(qreal x);
    qreal ypo5(qreal y, qreal x);

    qreal f8(qreal x, qreal y, qreal z);
    qreal g8(qreal x, qreal y, qreal z);
    qreal x08();
    qreal y08();
    qreal z08();
    qreal xFinish8();
    qreal h8();
    qreal yt8(qreal x);
    qreal ypo8(qreal y, qreal x);
public:
    explicit MyWidget(QWidget *parent = 0);

signals:

public slots:
    void print(const QString &msg);
    void process();
};

#endif // MYWIDGET_H
