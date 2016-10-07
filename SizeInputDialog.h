#ifndef SIZEINPUTDIALOG_H
#define SIZEINPUTDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class SizeInputDialog;
}

class SizeInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeInputDialog(QWidget *parent = 0);
    ~SizeInputDialog();

    void setImageSize(int width, int height);
    bool getImageSize(cv::Size&);

public slots:
    void on_width_changed();
    void on_height_changed();

private:
    Ui::SizeInputDialog *ui;

    cv::Size orgSize;
};

#endif // SIZEINPUTDIALOG_H
