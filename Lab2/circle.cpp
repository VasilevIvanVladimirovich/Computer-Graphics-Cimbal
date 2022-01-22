#include "circle.h"

Circle::Circle(QColor collor, QPoint center, qreal diametr)
{
    collor_ = collor;
    center_ = center;
    diametr_ = diametr;
}

Circle::Circle()
{

}

bool Circle::isFigureOnCoordinates(int x, int y)
{
    if(pow(x - center_.x(),2) + pow(y - center_.y(),2) <= pow(diametr_/2,2))
        return true;
    return false;
}

bool Circle::isFigureOnBorder(int x, int y)
{
    if(pow(x - center_.x(),2) + pow(y - center_.y(),2) == pow(diametr_/2,2))
        return true;
    return false;
}

void Circle::move(int x, int y)
{
    center_.rx() += x;
    center_.ry() += y;
}

int Circle::getXOnCoord(int y)
{
    return sqrt(pow(diametr_/2,2)-pow(y - center_.y(),2));
}

QPoint Circle::getCenter()
{
    return center_;
}

qreal Circle::getDiametr()
{
    return diametr_;
}

QColor Circle::getCollor()
{
    return collor_;
}

void Circle::setOtherCircle(QPoint center, qreal diametr, QColor collor)
{
    otherCenter.push_back(center);
    otherDiametr.push_back(diametr);
    otherCollor.push_back(collor);
}

void Circle::clearOtherCircle()
{
    otherCenter.clear();
    otherDiametr.clear();
    otherCollor.clear();
}

bool Circle::checkOtherCircle(int x,int y)
{
    for(int i = 0; i < otherCenter.count();i++)
    {
        if(pow(x - otherCenter[i].x(),2) + pow(y - otherCenter[i].y(),2) == pow(otherDiametr[i]/2,2))
            return true;
    }
    return false;
}




void Circle::paint(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::FlatCap));
    //painter.drawEllipse(center_.x()-diametr_/2, center_.y()-diametr_/2, diametr_, diametr_);

    QPoint point1,point2;
    int x;
    for(int y = center_.y()-diametr_/2; y <= center_.y()+diametr_/2;y++)
    {
        x = getXOnCoord(y);
        point1.rx() = center_.x() - x;
        point1.ry() = y;

        point2.rx() = center_.x() + x;
        point2.ry() = y;

        painter.setPen(QPen(collor_, 4, Qt::SolidLine, Qt::FlatCap));
        painter.drawLine(point1, point2);
    }

    //    for(int y = center_.y()-diametr_/2; y <= center_.y()+diametr_/2;y++)
    //    {
    //        x = getXOnCoord(y);
    //        point1.rx() = center_.x() - x;
    //        point1.ry() = y;

    //        if(checkOtherCircle(point1.rx(), point1.ry()))
    //        {
    //            painter.setPen(QPen(Qt::green, 10, Qt::SolidLine, Qt::FlatCap));
    //            painter.drawPoint(point1);
    //        }

    //        point2.rx() = center_.x() + x;
    //        point2.ry() = y;

    //        if(checkOtherCircle(point2.rx(), point2.ry()))
    //        {
    //            painter.setPen(QPen(Qt::green, 10, Qt::SolidLine, Qt::FlatCap));
    //            painter.drawPoint(point2);
    //        }

    ////        painter.setPen(QPen(collor_, 4, Qt::SolidLine, Qt::FlatCap));
    ////        painter.drawLine(point1, point2);
    //    }


}

