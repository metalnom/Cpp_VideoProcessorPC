#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

void MainWindow::Video_init()
{
    video >> frame_org;

    CV_Assert(frame_org.data);

    split(frame_org, bgr);
    cvtColor(frame_org, frame_gray, COLOR_BGR2GRAY);

    frame_rg = bgr[2]/2 + bgr[1]/2;     frame_gb = bgr[1]/2 + bgr[0]/2;     frame_br = bgr[0]/2 + bgr[2]/2;

    Size size = Size(256, 200);
    calc_Histo(bgr[2], r_hist, 256, 256);   draw_histo(r_hist, frame_r_hist, size);
    calc_Histo(bgr[1], g_hist, 256, 256);   draw_histo(g_hist, frame_g_hist, size);
    calc_Histo(bgr[0], b_hist, 256, 256);   draw_histo(b_hist, frame_b_hist, size);

    GaussianBlur(frame_org, frame_gauss, Size(blur_val, blur_val), 0);
    Canny(frame_org, frame_canny, edge_th1, edge_th2);

    frame_mov = frame_org;
}

void MainWindow::calc_Histo(const Mat& frame, Mat& hist, int bins, int range_max = 256) {
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float* ranges[] = {range};

    calcHist(&frame, 1, channels, Mat(), hist, 1, histSize, ranges);
}

void MainWindow::draw_histo(Mat hist, Mat&hist_frame, Size size = Size(256, 200)) {
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
