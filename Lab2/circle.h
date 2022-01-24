#ifndef CIRCLE_H
#define CIRCLE_H
#include <QObject>
#include <QPoint>
#include <QVector>
#include <QColor>
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

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
    void paint(QPainter &painter,int paintMode,qreal ingamma);

    int getXOnCoord(int y);
    int getXOnCoord(int y, QPoint center, qreal diametr);

    QPoint getCenter();
    qreal getDiametr();
    QColor getCollor();

    void setOtherCircle(QPoint center, qreal diametr, QColor collor);
    void clearOtherCircle();

    bool checkOtherCircle(int x,int y,int paintMode,qreal ingamma);

    void setColor(QColor c);
//    void setPlate(QPoint p1, QPoint p2);

private:
    QPoint center_;
    qreal diametr_;
    QColor qcollor_;

//    QPair<QPoint,QPoint> plate_;

    QColor newCollor;

    QVector<qreal> pointsForLines;

    QVector<QPoint> otherCenter;
    QVector<qreal> otherDiametr;
    QVector<QColor> otherCollor;
};


#endif // CIRCLE_H
