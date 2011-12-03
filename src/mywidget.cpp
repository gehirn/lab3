#include "mywidget.h"
#include "ui_form.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    ui = new Ui::Form();
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(process()));
    for (int i = 0; i <= 8; ++i)
    {
        ui->comboBox->addItem(QString("variant #%1").arg(i));
    }
    ui->comboBox->setCurrentIndex(8);
}

void MyWidget::print(const QString &msg)
{
    ui->plainTextEdit->appendPlainText(msg + '\n');
}

void MyWidget::process()
{
    ui->plainTextEdit->clear();
    variant = ui->comboBox->currentIndex();
    print(QString("Variant %1").arg(variant));
    print(QString("[%1; %2]").arg(x0(), 0, 'g', 5).arg(xFinish(), 0, 'g', 3));

    //calc

    qreal x = x0(), y = y0(), z = z0();
    for (int i = 1; x < xFinish() || qFuzzyCompare(x, xFinish()); ++i)
    {
        qreal k1 = h() * f(x, y, z);
        qreal q1 = h() * g(x, y, z);

        qreal k2 = h() * f(x + h() / 2.0, y + k1 / 2.0, z + q1 / 2.0);
        qreal q2 = h() * g(x + h() / 2.0, y + k1 / 2.0, z + q1 / 2.0);

        qreal k3 = h() * f(x + h() / 2.0, y + k2 / 2.0, z + q2 / 2.0);
        qreal q3 = h() * g(x + h() / 2.0, y + k2 / 2.0, z + q2 / 2.0);

        qreal k4 = h() * f(x + h(), y + k3, z + q3);
        qreal q4 = h() * g(x + h(), y + k3, z + q3);

        print(QString("#%1").arg(i));
        print(QString("y(%1) = %2").arg(x, 0, 'g', 5).arg(y, 0, 'g', 5));
        print(QString("y_ex(%1) = %2").arg(x, 0, 'g',5).arg(yt(x), 0, 'g', 5));
        print(QString("error(%1) = %2").arg(x, 0, 'g',5).arg(ypo(y, x), 0, 'g', 5));

        x += h();
        y += (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        z += (q1 + 2.0 * q2 + 2.0 * q3 + q4) / 6.0;

    }
}

qreal MyWidget::f(qreal x, qreal y, qreal z)
{
    switch (variant)
    {
    case 5: return f5(x, y, z);
    case 8: return f8(x, y, z);
    }
    return 0;
}

qreal MyWidget::g(qreal x, qreal y, qreal z)
{
    switch (variant)
    {
    case 5: return g5(x, y, z);
    case 8: return g8(x, y, z);
    }
    return 0;
}

qreal MyWidget::x0()
{
    switch (variant)
    {
    case 5: return x05();
    case 8: return x08();
    }
    return 0;
}

qreal MyWidget::y0()
{
    switch (variant)
    {
    case 5: return y05();
    case 8: return y08();
    }
    return 0;
}

qreal MyWidget::z0()
{
    switch (variant)
    {
    case 5: return z05();
    case 8: return z08();
    }
    return 0;
}

qreal MyWidget::xFinish()
{
    {
        switch (variant)
        {
        case 5: return xFinish5();
        case 8: return xFinish8();
        }
        return 0;
    }
}

qreal MyWidget::h()
{
    {
        switch (variant)
        {
        case 5: return h5();
        case 8: return h8();
        }
        return 0;
    }
}

qreal MyWidget::yt(qreal x)
{
    {
        switch (variant)
        {
        case 5: return yt5(x);
        case 8: return yt8(x);
        }
        return 0;
    }
}

qreal MyWidget::ypo(qreal y, qreal x)
{
    {
        switch (variant)
        {
        case 5: return ypo5(y, x);
        case 8: return ypo8(y, x);
        }
        return 0;
    }
}
// variant # 5
qreal MyWidget::f5(qreal x, qreal y, qreal z)
{
    return z;
}

qreal MyWidget::g5(qreal x, qreal y, qreal z)
{
    return 2*(exp(x) + z);
}

qreal MyWidget::x05()
{
    return 1;
}

qreal MyWidget::y05()
{
    return -1;
}

qreal MyWidget::z05()
{
    return 0;
}

qreal MyWidget::xFinish5()
{
    return 2;
}

qreal MyWidget::h5()
{
    return 0.1;
}

qreal MyWidget::yt5(qreal x)
{
    return qPow(qExp(1), 2 * x - 1) - 2 * qPow(qExp(1), x) + qExp(1) - 1;
}

qreal MyWidget::ypo5(qreal y, qreal x)
{
    return qAbs(y - yt5(x));
}

//variant #8
qreal MyWidget::f8(qreal x, qreal y, qreal z)
{
    return z;
}

qreal MyWidget::g8(qreal x, qreal y, qreal z)
{
    return - (pow(z, 2) + 1) / (pow(x, 2) + 1);
}

qreal MyWidget::x08()
{
    return 0;
}

qreal MyWidget::y08()
{
    return 1;
}

qreal MyWidget::z08()
{
    return 1;
}

qreal MyWidget::xFinish8()
{
    return 0.5;
}

qreal MyWidget::h8()
{
    return 0.05;
}
qreal MyWidget::yt8(qreal x)
{
    return (1 - x + 2 * log(1+x));
}

qreal MyWidget::ypo8(qreal y, qreal x)
{
    return qAbs (y - yt8(x));
}
