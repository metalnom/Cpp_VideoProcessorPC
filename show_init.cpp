#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

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
