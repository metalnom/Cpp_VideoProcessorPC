#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Blur_Edge_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);
    QImage qimg15(frame_gauss.data, frame_gauss.cols, frame_gauss.rows, frame_gauss.step, QImage::Format_RGB888);
    QImage qimg16(frame_canny.data, frame_canny.cols, frame_canny.rows, frame_canny.step, QImage::Format_Grayscale8);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));
    pixmap15.setPixmap( QPixmap::fromImage(qimg15.rgbSwapped()));
    pixmap16.setPixmap( QPixmap::fromImage(qimg16));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_GAUSS->fitInView(&pixmap15, Qt::KeepAspectRatio);
    ui->graphicsView_CANNY->fitInView(&pixmap16, Qt::KeepAspectRatio);
}
