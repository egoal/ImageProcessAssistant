#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class ContoursDisplayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent* e) override;

private slots:
    void on_actionOpen_triggered();

    void on_actionFit_triggered();

    void on_actionReset_triggered();

    void on_actionMakeGray_triggered();

    void on_actionMakeBinary_triggered();

    void on_actionSize_triggered();

    void on_actionInverse_triggered();

    void on_actionFindContours_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    ContoursDisplayer* contoursDisplayer{nullptr};

    cv::Mat srcImg;
    cv::Mat currentImg;
    std::string imgFileName;

    QImage qimgShow;
    float scale;
    bool showImage{true};

    void displayImage(const cv::Mat& img);

    void checkMenuWithCurrentImage();
};

#endif // MAINWINDOW_H
