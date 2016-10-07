#include "SizeInputDialog.h"
#include "ui_SizeInputDialog.h"

using namespace cv;

SizeInputDialog::SizeInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeInputDialog)
{
    ui->setupUi(this);

    connect(ui->ledtWidth, SIGNAL(textChanged(QString)), this, SLOT(on_width_changed()));
    connect(ui->ledtHeight, SIGNAL(textChanged(QString)), this, SLOT(on_height_changed()));
}

SizeInputDialog::~SizeInputDialog()
{
    delete ui;
}

void SizeInputDialog::setImageSize(int width, int height){
    orgSize =   Size(width, height);

    ui->ledtWidth->setText(QString("%1").arg(width));
    ui->ledtHeight->setText(QString("%1").arg(height));
}

bool SizeInputDialog::getImageSize(Size& s){
    bool wok    =   false;
    bool hok    =   false;
    s.width   =   ui->ledtWidth->text().toInt(&wok);
    s.height   =   ui->ledtHeight->text().toInt(&hok);

    return wok&&hok;
}

///
void SizeInputDialog::on_width_changed(){
    if(!ui->cboxRatio->isChecked())
        return;

    int w   =   ui->ledtWidth->text().toInt();
    ui->ledtHeight->setText(QString("%1").arg(w*orgSize.height/orgSize.width));
}
void SizeInputDialog::on_height_changed(){
    if(!ui->cboxRatio->isChecked())
        return;

    int h   =   ui->ledtHeight->text().toInt();
    ui->ledtWidth->setText(QString("%1").arg(h*orgSize.width/orgSize.height));
}
