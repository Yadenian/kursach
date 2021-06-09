#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSize>
#include <QToolBar>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_button_clicked();
private:
    void CreateMap();
    void RedrawCell(QPushButton* p);
    void RedrawIcons();
    void DeleteMap();
    void Move();
    int mapsize = 8;
    int cellsize = 70;
    int map[8][8] = {
        { 0,2,0,2,0,2,0,2 },
        { 2,0,2,0,2,0,2,0 },
        { 0,2,0,2,0,2,0,2 },
        { 0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0 },
        { 1,0,1,0,1,0,1,0 },
        { 0,1,0,1,0,1,0,1 },
        { 1,0,1,0,1,0,1,0 },
    };
    QPushButton* point1;
    QPushButton* point2;
    QGridLayout* l;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
