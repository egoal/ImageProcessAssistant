#include "SliderInput.h"

SliderInput::SliderInput(int* val, int min, int max, QString title){
    value   =   val;

    slider  =   new QSlider(Qt::Horizontal);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setValue(*val);

    QLabel* low =   new QLabel(QString::fromStdString(std::to_string(min)),this);
    QLabel* high =   new QLabel(QString::fromStdString(std::to_string(max)),this);
    theval   =   new QLineEdit(QString::fromStdString(std::to_string(*val)),this);

    btnOk   =   new QPushButton(tr("ok"));
    btnCancel   =   new QPushButton(tr("cancel"));

    //
    connect(slider, SIGNAL(sliderMoved(int)),this, SLOT(onSliderChanged(int)));
    connect(btnOk, SIGNAL(pressed()),this, SLOT(accept()));
    connect(btnCancel, SIGNAL(pressed()),this, SLOT(reject()));
    //

    QHBoxLayout* hl =   new QHBoxLayout;
    hl->addWidget(low);
    hl->addWidget(slider);
    hl->addWidget(high);
    hl->addWidget(theval);

    QHBoxLayout* hl2    =   new QHBoxLayout;
    hl2->addStretch();
    hl2->addWidget(btnOk);
    hl2->addWidget(btnCancel);

    QVBoxLayout* ml =   new QVBoxLayout;
    ml->addLayout(hl);
    ml->addLayout(hl2);
    this->setLayout(ml);
    this->setWindowTitle(title);

}

void SliderInput::onSliderChanged(int v){
    theval->setText(QString::fromStdString(std::to_string(v)));
    *value    =   v;

    emit value_changed(*value);
}
