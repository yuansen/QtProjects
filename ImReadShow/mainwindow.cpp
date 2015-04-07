#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include "opencv2/opencv.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_SelectImg_clicked()
{
    // Popup file dialog allowing user to select a file
    QString fname = QFileDialog::getOpenFileName(this,
                    tr("Select Image"), ".",
                    tr("JPG (*.jpg *.jpeg);;PNG (*.png);;TIFF (*.tiff *.tif)") );
    if (fname.isEmpty()) {
        this->ui->lb_fname->setText("Selected filename is empty.");
        return;
    }

    // Show file name
    this->ui->lb_fname->setText(fname);

    // Read image
    cv::Mat img = cv::imread(fname.toStdString());

    // Display image info
    if (img.empty()) {
        this->ui->lb_imgInfo->setText("Selected image is empty.");
        return;
    }
    this->ui->lb_imgInfo->setText("");
    this->ui->lb_imgInfo->setText( this->ui->lb_imgInfo->text() +
                                   "Height: " + QString::number(img.rows) + "\n" +
                                   "Width:  " + QString::number(img.cols) + "\n" +
                                   "Channels: " + QString::number(img.channels()) );

    // Show Image
    this->qLabelImShow(img, this->ui->lb_img);
}


void MainWindow::qLabelImShow(const cv::Mat& cimg, QLabel * qlabel)
{
    double widthScale  = qlabel->width()  * 1.0 / cimg.cols;
    double heightScale = qlabel->height() * 1.0 / cimg.rows;
    double scale = std::min(widthScale, heightScale);
    if (scale > 1.0) scale = 1.0;

    cv::Mat mat;
    cv::resize(cimg, mat, cv::Size(0,0), scale, scale);

    // 8-bits unsigned, NO. OF CHANNELS=1

    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage qimg(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        qimg.setColorTable(colorTable);
        qlabel->setPixmap(QPixmap::fromImage(qimg));
        qlabel->show();    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage qimg(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        qimg = qimg.rgbSwapped();
        qlabel->setPixmap(QPixmap::fromImage(qimg));
        qlabel->show();    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return;
    }

}
