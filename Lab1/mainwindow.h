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
#include <QCheckBox>
#include "figure.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow* parent = 0);
    ~MainWindow();

    void createFigure();

    bool isFigureOnCoordinates(int x, int y);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_btnCreateFigure_clicked();
    void on_btnMoveFigure_clicked();
    void on_btnRotateFigure_clicked();
    void on_btnScaleFigure_clicked();
    void on_btnTabulationFigure_clicked();
    void on_btnIsTreangle_clicked();

private:
    QString statusModeView[6] = {"View", "New", "Move", "Rotate","Scale","Tabulation"};
    QString statusMode;

    QPushButton* btnCreateFigure;
    QPushButton* btnMoveFigure;
    QPushButton* btnRotateFigure;
    QPushButton* btnScaleFigure;
    QPushButton* btnTabulationFigure;
    QPushButton* btnIsTreangle;

    QStatusBar* statusBar;

    QLabel* label_status;

    QVBoxLayout* layout_main;
    QHBoxLayout* layout_menu;
    QHBoxLayout* layout_graph;

    QVector<Figure> vectorFigure_;

    Figure *selectFugure_;
    QPoint selectPoint_;
    bool isSelection_=false;
    bool isTreangle = false;
};

#endif // MAINWINDOW_H
