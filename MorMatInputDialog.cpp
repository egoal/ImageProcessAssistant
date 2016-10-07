#include "MorMatInputDialog.h"
#include "ui_MorMatInputDialog.h"
#include <iostream>
#include <QtWidgets>

using namespace cv;

MorMatInputDialog::MorMatInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MorMatInput)
{
    ui->setupUi(this);

    // connect(ui->cboxType, SIGNAL(itemchanged), this, SLOT(updateMorMatAndEmit));
    connect(ui->cboxType, SIGNAL(currentIndexChanged(QString)),this, SLOT(updateMorMatAndEmit()));
    connect(ui->sboxWidth, SIGNAL(valueChanged(int)), this, SLOT(updateMorMatAndEmit()));
    connect(ui->sboxHeight, SIGNAL(valueChanged(int)), this, SLOT(updateMorMatAndEmit()));
    connect(ui->cboxSquared, &QCheckBox::stateChanged, [&](){
       if(ui->cboxSquared->isChecked()){
           connect(ui->sboxWidth, SIGNAL(valueChanged(int)), ui->sboxHeight, SLOT(setValue(int)));
           connect(ui->sboxHeight, SIGNAL(valueChanged(int)), ui->sboxWidth, SLOT(setValue(int)));
       }else{
           disconnect(ui->sboxWidth, SIGNAL(valueChanged(int)), ui->sboxHeight, SLOT(setValue(int)));
           disconnect(ui->sboxHeight, SIGNAL(valueChanged(int)), ui->sboxWidth, SLOT(setValue(int)));
       }
    });
}

MorMatInputDialog::~MorMatInputDialog()
{
    delete ui;
}

void MorMatInputDialog::updateMorMatAndEmit(){
    // std::cout<<"emit mormat"<<std::endl;
    if(!ui->cboxPreview->isChecked())
        return;

    QString typestr    =   ui->cboxType->currentText();
    int type    =   MORPH_RECT;
    if(typestr=="ellipse")
        type    =   MORPH_ELLIPSE;
    else if(typestr=="rectangle")
        type    =   MORPH_RECT;
    Size size(ui->sboxWidth->value(), ui->sboxHeight->value());

    Mat mat =   getStructuringElement(type, size);
    emit mormat_changed(mat);
}
