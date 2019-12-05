#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

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

void MainWindow::Show_init()
{
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

void MainWindow::RGB_show()
{
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

void MainWindow::Histo_show()
{
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

void MainWindow::Blur_Edge_show()
{
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

void MainWindow::Brightness_show()
{
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
