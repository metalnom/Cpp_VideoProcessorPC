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
    ~MainWindow();

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

void calc_Histo(const Mat&, Mat&, int, int);
void draw_histo(Mat, Mat&, Size);


#endif // MAINWINDOW_H
