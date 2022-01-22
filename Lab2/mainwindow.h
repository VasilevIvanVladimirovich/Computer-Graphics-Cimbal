#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <QColor>
#include <QRandomGenerator>
#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QStatusBar>
#include <QLabel>
#include "circle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   bool isFigureOnCoordinates(int x, int y);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_btnCreateCircle_clicked();
    void on_btnMoveCircle_clicked();
private:
    QString statusModeView[2] = {"View", "Move"};
    QString statusMode;

    QVBoxLayout* layout_main;
    QHBoxLayout* layout_menu;
    QHBoxLayout* layout_graph;

    QPushButton* btnCreateCircle;
    QPushButton* btnMoveCircle;

    QLabel* label_status;

    QStatusBar* statusBar;

    QVector<Circle> vectorCircle_;

    Circle* selectCircle_;
    QPoint selectPoint_;
    bool isSelection_=false;
};
#endif // MAINWINDOW_H
