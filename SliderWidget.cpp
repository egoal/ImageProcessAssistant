#include "SliderWidget.h"

SliderWidget::SliderWidget(QWidget *parent):QWidget(parent)
{}

SliderWidget::SliderWidget(int low, int high, int* val, QString valname, QWidget* parent) : QWidget(parent)
{
    init(low, high, val, valname);
}

void SliderWidget::init(int low, int high, int *val, QString valname){
    ptr_value   =   val;

    slider  =   new QSlider(Qt::Horizontal,this);
    slider->setMaximum(high);
    slider->setMinimum(low);
    slider->setValue(*val);
    edtValue    =   new QLineEdit;
    edtValue->setText(QString("%1").arg(*val));

    QHBoxLayout* ly =   new QHBoxLayout;
    if(!valname.isEmpty())
        ly->addWidget(new QLabel(valname));
    ly->addWidget(new QLabel(QString("%1").arg(low)));
    ly->addWidget(slider);
    ly->addWidget(new QLabel(QString("%1").arg(high)));
    ly->addWidget(edtValue);

    this->setLayout(ly);

    connect(slider, &QSlider::valueChanged,[&](int v){
        *ptr_value    =   slider->value();
        edtValue->setText(QString("%1").arg(*ptr_value));
        emit value_changed(v);
    });
}
