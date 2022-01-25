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
#include <QSlider>
#include <QTimer>
#include <QRadioButton>
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
    void sliderCollor_valueChanged(int);
    void on_btnGoCircle_clicked();
    void on_btnStopCircle_clicked();
    void on_isAdditivMixing_clicked();
    void on_isAverageMixing_clicked();
    void on_isGammaMixing_clicked();
    void updateRepaint();
private:
    QString statusModeView[3] = {"View", "Move","Movement"};
    QString statusMode;

    QVBoxLayout* layout_main;
    QHBoxLayout* layout_menu;
    QHBoxLayout* layout_graph;

    QSlider* sliderCollor;

    QPushButton* btnCreateCircle;
    QPushButton* btnMoveCircle;
    QPushButton* btnGoCircle;
    QPushButton* btnStopCircle;

    QRadioButton* isAdditivMixing;
    QRadioButton* isAverageMixing;
    QRadioButton* isGammaMixing;

    QLabel* label_status;
    QLabel* label_slider;

    QStatusBar* statusBar;

    QTimer* timer_;

    QVector<Circle> vectorCircle_;

    QTimer *timer_animation;

    Circle* selectCircle_;
    QPoint selectPoint_;
    bool isSelection_=false;

    int paintMode_ = 0;
};
#endif // MAINWINDOW_H
