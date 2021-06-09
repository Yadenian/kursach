#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(0,0,mapsize*cellsize + 20,mapsize*cellsize + 50);
    setMinimumSize(QSize(mapsize*cellsize + 20,mapsize*cellsize + 50));
    setMaximumSize(QSize(mapsize*cellsize + 20,mapsize*cellsize + 50));
    QList<QToolBar *> allToolBars = this->findChildren<QToolBar *>();
    l = new QGridLayout(this);
    foreach(QToolBar *tb, allToolBars) {
        this->removeToolBar(tb);
    }
    point1 = nullptr;
    point2 = nullptr;
    CreateMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedrawCell(QPushButton* p){
    if(p->x()/cellsize % 2 != 0){
        if(p->y()/cellsize % 2 == 0){
            p->setStyleSheet("background-color: gray");
        }
        else{
            p->setStyleSheet("background-color: white");
        }
    }
    else{
        if(p->y()/cellsize % 2 != 0){
            p->setStyleSheet("background-color: gray");
        }
        else{
            p->setStyleSheet("background-color: white");
        }
    }
}

void MainWindow::DeleteMap(){
    if (layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete layout();
    }
}

void MainWindow::Move(){

    int p1x = point1->x()/cellsize;
    int p1y = point1->y()/cellsize;
    int p2x = point2->x()/cellsize;
    int p2y = point2->y()/cellsize;

    if(map[p1y][p1x] == 1){
        if(point1 == point2){
            map[p1y][p1x] = 0;
            RedrawCell(point1);
            point1->setIcon(QIcon());
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(map[p1y][p1x] == 0){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p1x == p2x){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p1y == p2y){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p2y - p1y == 1){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(map[p2y][p2x] != 0){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(abs(p2y - p1y) > 2){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if((abs(p2x - p1x) == 2 && abs(p1y-p2y) == 1) || (abs(p2y - p1y) == 2 && abs(p1x-p2x) == 1)){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p2y == 0){
            map[p2y][p2x] = 3;
            map[p1y][p1x] = 0;
            QPixmap whiteimg(":/src/queenwhite.png");
            whiteimg = whiteimg.scaled(100,100,Qt::KeepAspectRatio,Qt::FastTransformation);
            point2->setIcon(whiteimg);
            point2->setIconSize(QSize(100,100));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else{
            map[p2y][p2x] = map[p1y][p1x];
            map[p1y][p1x] = 0;
            point2->setIcon(point1->icon());
            point2->setIconSize(QSize(70,70));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }

    }
    else if(map[p1y][p1x] == 2){
        if(point1 == point2){
            RedrawCell(point1);
            map[p1y][p1x] = 0;
            point1->setIcon(QIcon());
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(map[p1y][p1x] == 0){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(map[p2y][p2x] != 0){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p1x == p2x){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p1y == p2y){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p2y - p1y == -1){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if((abs(p2x - p1x) == 2 && abs(p1y-p2y) == 1) || (abs(p2y - p1y) == 2 && abs(p1x-p2x) == 1)){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(abs(p2y - p1y) > 2){
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else if(p2y == 7){
            map[p2y][p2x] = 4;
            map[p1y][p1x] = 0;
            QPixmap black(":/src/queenblack.png");
            black = black.scaled(70,70,Qt::KeepAspectRatio,Qt::FastTransformation);
            point2->setIcon(black);
            point2->setIconSize(QSize(70,70));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else{
            map[p2y][p2x] = map[p1y][p1x];
            map[p1y][p1x] = 0;
            point2->setIcon(point1->icon());
            point2->setIconSize(QSize(70,70));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
    }
    else if(map[p1y][p1x] == 3){
        if(abs(p1x - p2x) / abs(p1y - p2y) == 1){
            map[p2y][p2x] = map[p1y][p1x];
            map[p1y][p1x] = 0;
            point2->setIcon(point1->icon());
            point2->setIconSize(QSize(100,100));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else{
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
    }
    else if(map[p1y][p1x] == 4){
        if(abs(p1x - p2x) / abs(p1y - p2y) == 1){
            map[p2y][p2x] = map[p1y][p1x];
            map[p1y][p1x] = 0;
            point2->setIcon(point1->icon());
            point2->setIconSize(QSize(70,70));
            point1->setIcon(QIcon());
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
        else{
            RedrawCell(point1);
            point1 = nullptr;
            point2 = nullptr;
            return;
        }
    }
    else{
        RedrawCell(point1);
        point1 = nullptr;
        point2 = nullptr;
        return;
    }
}

void MainWindow::on_button_clicked(){
    QPushButton* pressedButton = qobject_cast<QPushButton*>(sender());
    if(point1 == nullptr){
        point1 = pressedButton;
        point1->setStyleSheet("background-color: red");
    }
    else if(point2 == nullptr){
        point2 = pressedButton;
        Move();
    }
    qDebug() << "You clicked " << pressedButton;
    qDebug() << "X: " << pressedButton->x()/cellsize;
    qDebug() << "Y: " << pressedButton->y()/cellsize;
}

void MainWindow::CreateMap(){
    QPixmap whiteimg(":/src/white.png");
    whiteimg = whiteimg.scaled(70,70,Qt::KeepAspectRatio,Qt::FastTransformation);
    QPixmap blackimg(":/src/black.png");
    blackimg = blackimg.scaled(70,70,Qt::KeepAspectRatio,Qt::FastTransformation);
    setLayout(l);
    for(int i = 0; i < mapsize; i++){
        for(int j = 0; j < mapsize; j++){
            QPushButton* c = new QPushButton(this);
            QObject::connect(c,SIGNAL(clicked()),this,SLOT(on_button_clicked()));
            if(map[i][j] == 2){
                c->setIcon(blackimg);
                c->setIconSize(QSize(70,70));
                qDebug() << "X: " << c->x();
                qDebug() << "Y: " << c->y();
            }
            else if(map[i][j] == 1){
                c->setIcon(whiteimg);
                c->setIconSize(QSize(70,70));
            }
            c->setGeometry(j*cellsize+10,i*cellsize+10,70,70);
            l->addWidget(c);
            c->show();
            if(i % 2 != 0){
                if(j % 2 == 0){
                    c->setStyleSheet("background-color: gray");
                }
                else{
                    c->setStyleSheet("background-color: white");
                }
            }
            else{
                if(j % 2 != 0){
                    c->setStyleSheet("background-color: gray");
                }
                else{
                    c->setStyleSheet("background-color: white");
                }
            }
        }
    }
}

