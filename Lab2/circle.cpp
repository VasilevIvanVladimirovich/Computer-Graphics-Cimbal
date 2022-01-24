#include "circle.h"

Circle::Circle(QColor collor, QPoint center, qreal diametr)
{
    qcollor_ = collor;
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
//    if(center_.x() + x - diametr_/2 > plate_.first.x() &&  center_.x() + x + diametr_/2 <  plate_.second.x() &&
//       center_.y() + y - diametr_/2> plate_.first.y() &&  center_.y() + y + diametr_/2 <  plate_.second.y())
//    {
        center_.rx() += x;
        center_.ry() += y;
//    }
}

int Circle::getXOnCoord(int y)
{
    return sqrt(pow(diametr_/2,2)-pow(y - center_.y(),2));
}

int Circle::getXOnCoord(int y, QPoint center, qreal diametr)
{
    return sqrt(pow(diametr/2,2)-pow(y - center.y(),2));
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
    return qcollor_;
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

bool Circle::checkOtherCircle(int x,int y, int paintMode,qreal ingamma)
{
    int newR,newG,newB;
    qcollor_.getRgb(&newR,&newG,&newB);
    newCollor.setRgb(newR,newG,newB);

    int R,G,B;
    qreal gamma = ingamma;

    int sumR=newR, sumG=newG, sumB=newB;
    int countCollor=1;

    bool result = false;
    for(int i = 0; i < otherCenter.count();i++)
    {
        if(pow(x - otherCenter[i].x(),2) + pow(y - otherCenter[i].y(),2) <= pow(otherDiametr[i]/2,2))
        {
            if(paintMode == 1)
            {
                otherCollor[i].getRgb(&R,&G,&B);
                newR = std::min(newR + R,255);
                newG = std::min(newG + G,255);
                newB = std::min(newB + B,255);
                newCollor.setRgb(newR,newG,newB);
                result = true;
            }
            if(paintMode == 2|| paintMode ==3)
            {
                otherCollor[i].getRgb(&R,&G,&B);
                sumR = newR + R;
                sumG = newG + G;
                sumB = newB + B;
                countCollor++;
                result = true;
            }
        }

    }
    if(paintMode == 2||paintMode == 3)
    {
        sumR = sumR/countCollor;
        sumG = sumG/countCollor;
        sumB = sumB/countCollor;
        newCollor.setRgb(sumR,sumG,sumB);
    }
    if(paintMode == 3)
    {
        newCollor.getRgb(&R,&G,&B);
        R = 255 * pow(double(R)/255,gamma);
        G = 255 * pow(double(G)/255,gamma);
        B = 255 * pow(double(B)/255,gamma);
        newCollor.setRgb(R,G,B);
        result = true;
    }
    return result;
}

void Circle::setColor(QColor c)
{
    qcollor_ = c;
}

//void Circle::setPlate(QPoint p1, QPoint p2)
//{
//    plate_ = qMakePair(p1,p2);
//}


void Circle::paint(QPainter &painter, int paintMode, qreal ingamma)
{
    painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::FlatCap));

    QPoint point1,point2;
    qreal x, x1, x2;
    for(int y = center_.y()-diametr_/2; y <= center_.y()+diametr_/2;y++)
    {
        pointsForLines.clear();
        x = getXOnCoord(y);

        x1 = center_.x() - x;
        point1.rx() = x1;
        point1.ry() = y;

        pointsForLines.push_back(x1);

        x2 = center_.x() + x;
        point2.rx() = x2;
        point2.ry() = y;

        painter.setPen(QPen(qcollor_, 4, Qt::SolidLine, Qt::FlatCap));

        qreal xi, xi1, xi2;
        for(int i = 0; i < otherCenter.count();i++)
        {
            xi = getXOnCoord(y, otherCenter[i], otherDiametr[i]);
            xi1 = otherCenter[i].x() - xi;
            xi2 = otherCenter[i].x() + xi;

            if(x1 <= xi1 && xi1 <= x2 ){
                pointsForLines.push_back(xi1);
            }
            if(xi2 <= x2 && xi2 >= x1){
                pointsForLines.push_back(xi2);
            }
        }
        pointsForLines.push_back(x2);
        std::sort(pointsForLines.begin(),pointsForLines.end());
        for(int i = 0; i < pointsForLines.count()-1;i++)
        {
            if(checkOtherCircle(pointsForLines[i]+1, y, paintMode,ingamma))
            {
                painter.setPen(QPen(newCollor, 4, Qt::SolidLine, Qt::FlatCap));
                painter.drawLine(pointsForLines[i],y, pointsForLines[i+1],y);
            }else{
                painter.setPen(QPen(qcollor_, 4, Qt::SolidLine, Qt::FlatCap));
                painter.drawLine(pointsForLines[i],y, pointsForLines[i+1],y);
            }
        }
    }
}

