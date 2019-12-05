#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include "opencv2/opencv.hpp"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int rot;
    int brightness = 0;
    int blur_val = 55;
    int edge_th1 = 100;
    int edge_th2 = 150;
    Mat frame_org, frame_gray, frame_rg, frame_gb, frame_br, frame_det;
    Mat bgr[3];
    Mat r_hist, g_hist, b_hist;
    Mat frame_r_hist, frame_g_hist, frame_b_hist, frame_gauss, frame_canny, frame_mov, frame_bright;

    ~MainWindow();

    void RGB_show();
    void Histo_show();
    void Blur_Edge_show();
    void Move_show();
    void Detect_show();
    void Brightness_show();
    void Show_init();
    void Video_init();
    void calc_Histo(const Mat&, Mat&, int, int);
    void draw_histo(Mat, Mat&, Size);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_startBtn_MAIN_pressed();
    void on_pushButtonRCCW_pressed();
    void on_pushButtonTORG_pressed();
    void on_pushButtonRCW_pressed();
    void on_pushButton_MOV_UP_clicked();
    void on_pushButton_MOV_DOWN_clicked();
    void on_pushButton_MOV_LEFT_clicked();
    void on_pushButton_MOV_RIGHT_clicked();
    void on_pushButton_MOV_HOME_clicked();
    void on_pushButton_MOV_zin_clicked();
    void on_pushButton_MOV_zout_clicked();
    void on_startBtn_REC_pressed();
    void on_startBtn_CAP_pressed();
    void on_pushButton_BR_PLUS_pressed();
    void on_pushButton_BR_MINUS_pressed();
    void on_BlurSlider_valueChanged(int value);
    void on_EdgeSlider_1_valueChanged(int value);
    void on_EdgeSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem pixmap01, pixmap02, pixmap03, pixmap04, pixmap05,\
                        pixmap06, pixmap07, pixmap08, pixmap09, pixmap10,\
                        pixmap11, pixmap12, pixmap13, pixmap14, pixmap15,\
                        pixmap16, pixmap17, pixmap18, pixmap19;
    cv::VideoCapture video;
};

#endif // MAINWINDOW_H
