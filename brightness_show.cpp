#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Brightness_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    frame_org.convertTo(frame_bright, -1, 1, brightness);
    QImage qimg19(frame_bright.data, frame_bright.cols, frame_bright.rows, frame_bright.step, QImage::Format_RGB888);
    pixmap19.setPixmap( QPixmap::fromImage(qimg19.rgbSwapped()));
    ui->graphicsView_Bright->fitInView(&pixmap19, Qt::KeepAspectRatio);
    ui->BR_Number->display(brightness);
}
