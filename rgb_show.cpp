#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::RGB_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);
    QImage qimg03(bgr[2].data, bgr[2].cols, bgr[2].rows, bgr[2].step, QImage::Format_Grayscale8);
    QImage qimg04(bgr[1].data, bgr[1].cols, bgr[1].rows, bgr[1].step, QImage::Format_Grayscale8);
    QImage qimg05(bgr[0].data, bgr[0].cols, bgr[0].rows, bgr[0].step, QImage::Format_Grayscale8);
    QImage qimg06(frame_rg.data, frame_rg.cols, frame_rg.rows, frame_rg.step, QImage::Format_Grayscale8);
    QImage qimg07(frame_gb.data, frame_gb.cols, frame_gb.rows, frame_gb.step, QImage::Format_Grayscale8);
    QImage qimg08(frame_br.data, frame_br.cols, frame_br.rows, frame_br.step, QImage::Format_Grayscale8);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));
    pixmap03.setPixmap( QPixmap::fromImage(qimg03));
    pixmap04.setPixmap( QPixmap::fromImage(qimg04));
    pixmap05.setPixmap( QPixmap::fromImage(qimg05));
    pixmap06.setPixmap( QPixmap::fromImage(qimg06));
    pixmap07.setPixmap( QPixmap::fromImage(qimg07));
    pixmap08.setPixmap( QPixmap::fromImage(qimg08));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_R->fitInView(&pixmap03, Qt::KeepAspectRatio);
    ui->graphicsView_G->fitInView(&pixmap04, Qt::KeepAspectRatio);
    ui->graphicsView_B->fitInView(&pixmap05, Qt::KeepAspectRatio);
    ui->graphicsView_RG->fitInView(&pixmap06, Qt::KeepAspectRatio);
    ui->graphicsView_GB->fitInView(&pixmap07, Qt::KeepAspectRatio);
    ui->graphicsView_BR->fitInView(&pixmap08, Qt::KeepAspectRatio);
}
