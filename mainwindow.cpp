#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->graphicsView_org->setScene(new QGraphicsScene(this));
    ui->graphicsView_R->setScene(new QGraphicsScene(this));
    ui->graphicsView_G->setScene(new QGraphicsScene(this));
    ui->graphicsView_B->setScene(new QGraphicsScene(this));
    ui->graphicsView_RG->setScene(new QGraphicsScene(this));
    ui->graphicsView_GB->setScene(new QGraphicsScene(this));
    ui->graphicsView_BR->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_R->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_G->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_B->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_RH->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_GH->setScene(new QGraphicsScene(this));
    ui->graphicsView_H_BH->setScene(new QGraphicsScene(this));
    ui->graphicsView_ROT->setScene(new QGraphicsScene(this));
    ui->graphicsView_GAUSS->setScene(new QGraphicsScene(this));
    ui->graphicsView_CANNY->setScene(new QGraphicsScene(this));
    ui->graphicsView_MOV->setScene(new QGraphicsScene(this));
    ui->graphicsView_DET->setScene(new QGraphicsScene(this));
    ui->graphicsView_Bright->setScene(new QGraphicsScene(this));

    ui->graphicsView_org->scene()->addItem(&pixmap01);
    ui->graphicsView_R->scene()->addItem(&pixmap03);
    ui->graphicsView_G->scene()->addItem(&pixmap04);
    ui->graphicsView_B->scene()->addItem(&pixmap05);
    ui->graphicsView_RG->scene()->addItem(&pixmap06);
    ui->graphicsView_GB->scene()->addItem(&pixmap07);
    ui->graphicsView_BR->scene()->addItem(&pixmap08);
    ui->graphicsView_H_R->scene()->addItem(&pixmap09);
    ui->graphicsView_H_G->scene()->addItem(&pixmap10);
    ui->graphicsView_H_B->scene()->addItem(&pixmap11);
    ui->graphicsView_H_RH->scene()->addItem(&pixmap12);
    ui->graphicsView_H_GH->scene()->addItem(&pixmap13);
    ui->graphicsView_H_BH->scene()->addItem(&pixmap14);
    ui->graphicsView_ROT->scene()->addItem(&pixmap02);
    ui->graphicsView_GAUSS->scene()->addItem(&pixmap15);
    ui->graphicsView_CANNY->scene()->addItem(&pixmap16);
    ui->graphicsView_MOV->scene()->addItem(&pixmap17);
    ui->graphicsView_DET->scene()->addItem(&pixmap18);
    ui->graphicsView_Bright->scene()->addItem(&pixmap19);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_startBtn_MAIN_pressed() {
    if(video.isOpened()) {
        ui->startBtn_MAIN->setText("Start");
        video.release();
        return;
    }

    bool isCamera;
    int cameraIndex = ui->CameraIndex->text().toInt(&isCamera);
    if(isCamera) {
        if(!video.open(cameraIndex)) {
            QMessageBox::critical(this, "Camera Error", "Make sure you entered a correct camera index," "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }
    else {
        if(!video.open(ui->CameraIndex->text().trimmed().toStdString())) {
            QMessageBox::critical(this, "Video Error", "Make sure you entered a correct and supported video file path," "<br>or a correct RTSP feed URL!");
            return;
        }
    }

    ui->startBtn_MAIN->setText("Stop");

    Mat frame_org, frame_gray, frame_rg, frame_gb, frame_br, frame_det;

    video.set(3, 640);
    video.set(4, 480);

    while(video.isOpened()) {
        video >> frame_org;

        Mat bgr[3];
        CV_Assert(frame_org.data);

        split(frame_org, bgr);
        cvtColor(frame_org, frame_gray, COLOR_BGR2GRAY);

        frame_rg = bgr[2]/2 + bgr[1]/2;     frame_gb = bgr[1]/2 + bgr[0]/2;     frame_br = bgr[0]/2 + bgr[2]/2;

        Mat r_hist, g_hist, b_hist;
        Mat frame_r_hist, frame_g_hist, frame_b_hist, frame_gauss, frame_canny, frame_mov, frame_bright;

        Size size = Size(256, 200);
        calc_Histo(bgr[2], r_hist, 256, 256);   draw_histo(r_hist, frame_r_hist, size);
        calc_Histo(bgr[1], g_hist, 256, 256);   draw_histo(g_hist, frame_g_hist, size);
        calc_Histo(bgr[0], b_hist, 256, 256);   draw_histo(b_hist, frame_b_hist, size);

        GaussianBlur(frame_org, frame_gauss, Size(blur_val, blur_val), 0);
        Canny(frame_org, frame_canny, edge_th1, edge_th2);

        frame_mov = frame_org;

        if(ui->tabWidget->currentIndex() == 0) {
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

        if(ui->tabWidget->currentIndex() == 1) {
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

        if(ui->tabWidget->currentIndex() == 2) {
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

        if(ui->tabWidget->currentIndex() == 3) {
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

        if(ui->tabWidget->currentIndex() == 4) {
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
            }ui->BlurSlider->setValue(blur_val);
            if(blur_val%2 == 0) blur_val += 1;

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

        if(ui->tabWidget->currentIndex() == 5) {
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

        qApp->processEvents();
    }
    ui->startBtn_MAIN->setText("Start");
}


void MainWindow::closeEvent(QCloseEvent *event) {
    if(video.isOpened()) {
        QMessageBox::warning(this, "Warning", "Stop the video before closing the application!");
        event->ignore();
    }
    else {
        event->accept();
    }
}
