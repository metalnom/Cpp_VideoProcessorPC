#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::on_pushButtonRCCW_pressed() {
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->rotate(-10);
}
void MainWindow::on_pushButtonTORG_pressed() {
    ui->graphicsView_ROT->resetMatrix();
}

void MainWindow::on_pushButtonRCW_pressed() {
    ui->graphicsView_ROT->fitInView(&pixmap02, Qt::KeepAspectRatio);
    ui->graphicsView_ROT->rotate(10);
}

void MainWindow::on_pushButton_MOV_UP_clicked() {
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x(), ui->graphicsView_MOV->y() - 10);
}

void MainWindow::on_pushButton_MOV_DOWN_clicked() {
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x(), ui->graphicsView_MOV->y() + 10);
}

void MainWindow::on_pushButton_MOV_LEFT_clicked() {
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x() - 10, ui->graphicsView_MOV->y());
}

void MainWindow::on_pushButton_MOV_RIGHT_clicked() {
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x() + 10, ui->graphicsView_MOV->y());
}

void MainWindow::on_pushButton_MOV_HOME_clicked() {
    ui->graphicsView_MOV->move(160, 130);
    ui->graphicsView_MOV->resize(256, 192);
}

void MainWindow::on_pushButton_MOV_zin_clicked() {
    ui->graphicsView_MOV->resize(ui->graphicsView_MOV->width() + 12, ui->graphicsView_MOV->height() + 12);
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x() - 6, ui->graphicsView_MOV->y() - 6);
}

void MainWindow::on_pushButton_MOV_zout_clicked() {
    ui->graphicsView_MOV->resize(ui->graphicsView_MOV->width() - 12, ui->graphicsView_MOV->height() - 12);
    ui->graphicsView_MOV->move(ui->graphicsView_MOV->x() + 6, ui->graphicsView_MOV->y() + 6);
}

void MainWindow::on_startBtn_REC_pressed() {
    Rec_func();
}

void MainWindow::on_startBtn_CAP_pressed() {
    Cap_func();
}

void MainWindow::on_pushButton_BR_PLUS_pressed() {
    brightness += 15;
    if(brightness >= 255) brightness = 255;
}

void MainWindow::on_pushButton_BR_MINUS_pressed() {
    brightness -= 15;
    if(brightness <= -255) brightness = -255;
}

void MainWindow::on_BlurSlider_valueChanged(int value) {
    blur_val = value;
    if(blur_val%2 == 0) blur_val += 1;
}

void MainWindow::on_EdgeSlider_1_valueChanged(int value) {
    edge_th1 = value;
}

void MainWindow::on_EdgeSlider_2_valueChanged(int value) {
    edge_th2 = value;
}
