#ifndef SPRITESETTINGWIDGET_H
#define SPRITESETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SpriteSettingWidget;
}

class SpriteSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpriteSettingWidget(QWidget *parent = 0);
    ~SpriteSettingWidget();

private:
    Ui::SpriteSettingWidget *ui;
};

#endif // SPRITESETTINGWIDGET_H
