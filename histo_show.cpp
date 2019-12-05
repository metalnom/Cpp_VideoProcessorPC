#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Histo_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);
    QImage qimg09(bgr[2].data, bgr[2].cols, bgr[2].rows, bgr[2].step, QImage::Format_Grayscale8);
    QImage qimg10(bgr[1].data, bgr[1].cols, bgr[1].rows, bgr[1].step, QImage::Format_Grayscale8);
    QImage qimg11(bgr[0].data, bgr[0].cols, bgr[0].rows, bgr[0].step, QImage::Format_Grayscale8);
    QImage qimg12(frame_r_hist.data, frame_r_hist.cols, frame_r_hist.rows, frame_r_hist.step, QImage::Format_Grayscale8);
    QImage qimg13(frame_g_hist.data, frame_g_hist.cols, frame_g_hist.rows, frame_g_hist.step, QImage::Format_Grayscale8);
    QImage qimg14(frame_b_hist.data, frame_b_hist.cols, frame_b_hist.rows, frame_b_hist.step, QImage::Format_Grayscale8);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));
    pixmap09.setPixmap( QPixmap::fromImage(qimg09));
    pixmap10.setPixmap( QPixmap::fromImage(qimg10));
    pixmap11.setPixmap( QPixmap::fromImage(qimg11));
    pixmap12.setPixmap( QPixmap::fromImage(qimg12));
    pixmap13.setPixmap( QPixmap::fromImage(qimg13));
    pixmap14.setPixmap( QPixmap::fromImage(qimg14));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_H_R->fitInView(&pixmap09, Qt::KeepAspectRatio);
    ui->graphicsView_H_G->fitInView(&pixmap10, Qt::KeepAspectRatio);
    ui->graphicsView_H_B->fitInView(&pixmap11, Qt::KeepAspectRatio);
    ui->graphicsView_H_RH->fitInView(&pixmap12, Qt::KeepAspectRatio);
    ui->graphicsView_H_GH->fitInView(&pixmap13, Qt::KeepAspectRatio);
    ui->graphicsView_H_BH->fitInView(&pixmap14, Qt::KeepAspectRatio);
}
