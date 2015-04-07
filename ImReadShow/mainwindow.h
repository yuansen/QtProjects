#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void qLabelImShow(const cv::Mat& mat, QLabel * qlabel);

private slots:
    void on_pb_SelectImg_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
