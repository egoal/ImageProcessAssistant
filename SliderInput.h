#pragma once

#include <QtWidgets>

class SliderInput: public QDialog
{
    Q_OBJECT
public:
    SliderInput(int* val, int min, int max, QString title = "");

    // void addSlideValue(int& val, int min, int max);
signals:
    void value_changed(int);

private slots:
    void onSliderChanged(int);

private:
    QSlider* slider;
    QLineEdit* theval;
    QPushButton* btnOk, *btnCancel;

    int* value;
};
