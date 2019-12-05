#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Show_init();
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

    video.set(3, 640);
    video.set(4, 480);

    while(video.isOpened()) {
        Video_init();

        if(ui->tabWidget->currentIndex() == 0) RGB_show();
        if(ui->tabWidget->currentIndex() == 1) Histo_show();
        if(ui->tabWidget->currentIndex() == 2) Blur_Edge_show();
        if(ui->tabWidget->currentIndex() == 3) Move_show();
        if(ui->tabWidget->currentIndex() == 4) Detect_show();
        if(ui->tabWidget->currentIndex() == 5) Brightness_show();

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
