#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Move_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);
    QImage qimg17(frame_mov.data, frame_mov.cols, frame_mov.rows, frame_mov.step, QImage::Format_RGB888);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));
    pixmap17.setPixmap( QPixmap::fromImage(qimg17.rgbSwapped()));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_MOV->fitInView(&pixmap17, Qt::KeepAspectRatio);
}
