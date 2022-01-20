#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QPoint>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QtMath>

#include <cmath>
#include <algorithm>
#include <functional>

#include <QDebug>

class Figure
{
public:
    Figure(QColor collor);
    Figure();

    void add_point(int x, int y);
    void set_collor(QColor collor);
    void paint(QPainter &painter, QVector<Figure>& triangles);
    void paint(QPainter &Painter,QColor &collor);
    void move(int x, int y);
    void rotate();
    bool isFigureOnCoordinates(int x, int y);
    void closeShape();
    QPoint getFirstPoint();
    void setFirstPoint(int x, int y);
    int getCountPoint();
    bool isEmpty();
    void findCenter();
    QPoint findCenter(const QVector<QPoint> &points);
    void setAngle(QPoint selectPoint, QPoint current);
    void setScale(int posX,int posY, QPoint& selectedPoint);
    void scale();
    QVector<Figure> triangulate();
    void sortPointsClock();
    static bool compare_points_of_center(const QPoint &p1, const QPoint &p2, const QPoint &center);
    void paintTriangles(QPainter& painter);
    static QVector<QPair<QPoint, QPoint>> cyrusBeck(const QPair<QPoint, QPoint> &line, const Figure &shape);
private:
    QPoint center_;
    QVector<QPoint> points_;
    QVector<QPair<QPoint, QPoint>> lines_;
    QColor collor_;
    qreal angle_;
    qreal scale_;
};

#endif // FIGURE_H
