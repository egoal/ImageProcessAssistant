#include "SpriteSettingWidget.h"
#include "ui_SpriteSettingWidget.h"

SpriteSettingWidget::SpriteSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpriteSettingWidget)
{
    ui->setupUi(this);
}

SpriteSettingWidget::~SpriteSettingWidget()
{
    delete ui;
}
