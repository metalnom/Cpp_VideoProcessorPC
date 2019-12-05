#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Detect_show()
{
    QImage qimg01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step, QImage::Format_RGB888);
    QImage qimg02(frame_gray.data, frame_gray.cols, frame_gray.rows, frame_gray.step, QImage::Format_Grayscale8);

    pixmap01.setPixmap( QPixmap::fromImage(qimg01.rgbSwapped()));
    pixmap02.setPixmap( QPixmap::fromImage(qimg02));

    ui->graphicsView_org->fitInView(&pixmap01, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);

    video >> frame_det;
    CascadeClassifier classifier;

    if(ui->radioButton_car->isChecked()) {
        classifier.load("haarcascade_cars.xml");
        vector<Rect> detecs;
        classifier.detectMultiScale(frame_det, detecs);
        for(Rect rc : detecs) {
            rectangle(frame_det, rc, Scalar(255, 0, 255), 2);
        }
        QImage qimg18(frame_det.data, frame_det.cols, frame_det.rows, frame_det.step, QImage::Format_RGB888);
        pixmap18.setPixmap( QPixmap::fromImage(qimg18.rgbSwapped()));
    }

    if(ui->radioButton_face->isChecked()) {
        classifier.load("haarcascade_frontalface_default.xml");
        vector<Rect> detecs;
        classifier.detectMultiScale(frame_det, detecs);
        for(Rect rc : detecs) {
            rectangle(frame_det, rc, Scalar(255, 0, 255), 2);
        }
        QImage qimg18(frame_det.data, frame_det.cols, frame_det.rows, frame_det.step, QImage::Format_RGB888);
        pixmap18.setPixmap( QPixmap::fromImage(qimg18.rgbSwapped()));
        ui->graphicsView_DET->fitInView(&pixmap18, Qt::KeepAspectRatio);
    }
}
