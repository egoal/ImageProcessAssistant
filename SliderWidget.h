#ifndef SLIDERWIDGET_H
#define SLIDERWIDGET_H

#include <QtWidgets>

class SliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidget(QWidget* parent=nullptr);
    explicit SliderWidget(int low, int high, int* val, QString name = "", QWidget* parent = nullptr);

    void init(int low, int high, int* val, QString name);
signals:
    void value_changed(int);
public slots:

private:
    int* ptr_value;
    QSlider* slider;
    QLineEdit* edtValue;
};

#endif // SLIDERWIDGET_H
