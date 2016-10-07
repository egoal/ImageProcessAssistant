#ifndef MORMATINPUTDIALOG_H
#define MORMATINPUTDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
class MorMatInput;
}

class MorMatInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MorMatInputDialog(QWidget *parent = 0);
    ~MorMatInputDialog();

public slots:
    void updateMorMatAndEmit();

signals:
    void mormat_changed(cv::Mat);

private:
    Ui::MorMatInput *ui;


};

#endif // MORMATINPUTDIALOG_H
