#ifndef CIRCLE_H
#define CIRCLE_H
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

class Circle
{
public:
    Circle(QColor collor, QPoint center, qreal diametr);
    Circle();

    bool isFigureOnCoordinates(int x, int y);
    bool isFigureOnBorder(int x, int y);
    void move(int x, int y);
    void paint(QPainter &painter);

    int getXOnCoord(int y);

    QPoint getCenter();
    qreal getDiametr();
    QColor getCollor();

    void setOtherCircle(QPoint center, qreal diametr, QColor collor);
    void clearOtherCircle();

    bool checkOtherCircle(int x,int y);

private:
    QPoint center_;
    qreal diametr_;
    QColor collor_;

    QVector<QPoint> otherCenter;
    QVector<qreal> otherDiametr;
    QVector<QColor> otherCollor;
};


#endif // CIRCLE_H
