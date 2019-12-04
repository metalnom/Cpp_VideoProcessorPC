#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace cv;
using namespace std;

void calc_Histo(const Mat& frame, Mat& hist, int bins, int range_max = 256) {
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float* ranges[] = {range};

    calcHist(&frame, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void draw_histo(Mat hist, Mat&hist_frame, Size size = Size(256, 200)) {
    hist_frame = Mat(size, CV_8U, Scalar(255));
    float bin = (float)hist_frame.cols / hist.rows;
    normalize(hist, hist, 0, hist_frame.rows, NORM_MINMAX);

    for(int i = 0; i < hist.rows; i++) {
        float start_x = i * bin;
        float end_x = (i + 1) * bin;
        Point2f pt1(start_x, 0);
        Point2f pt2(end_x, hist.at<float>(i));

        if(pt2.y > 0) {
            rectangle(hist_frame, pt1, pt2, Scalar(0), -1);
        }
    }
    flip(hist_frame, hist_frame, 0);
}

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
    ui->startBtn_REC->setText("Stop");
    string rec_path = ui->PATH_REC->text().toStdString();

    Size size = Size((int)video.get(CAP_PROP_FRAME_WIDTH), (int)video.get(CAP_PROP_FRAME_HEIGHT));
    int fourcc = VideoWriter::fourcc('M','P','4','2');
    double fps = 10;
    int delay = cvRound(1000.0 / fps);

    VideoWriter writer = VideoWriter(rec_path, fourcc, fps, size);
    while(1) {
        Mat frame_rec;
        video >> frame_rec;
        writer << frame_rec;
        imshow("rec", frame_rec);
        if(waitKey(delay) >= 0) {
            break;
        }
    }
    writer.release();
    destroyWindow("rec");
    ui->startBtn_REC->setText("RECORD");
    cout << "Recording finished!" << endl;
}

void MainWindow::on_startBtn_CAP_pressed() {
    string cap_path = ui->PATH_CAP->text().toStdString();
    Mat frame_cap;
    video >> frame_cap;
    imwrite(cap_path, frame_cap);
    Mat img = imread(cap_path);
    imshow("captured image", img);
    waitKey(0);
    destroyWindow("captured image");
}
