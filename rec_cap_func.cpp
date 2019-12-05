#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Rec_func()
{
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

void MainWindow::Cap_func()
{
    string cap_path = ui->PATH_CAP->text().toStdString();
    Mat frame_cap;
    video >> frame_cap;
    imwrite(cap_path, frame_cap);
    Mat img = imread(cap_path);
    imshow("captured image", img);
    waitKey(0);
    destroyWindow("captured image");
}
