#include "figure.h"

Figure::Figure(QColor collor)
{
    collor_ = collor;
    angle_ = 0.0;
    scale_ = 1.0;
}

Figure::Figure()
{
    angle_ = 0.0;
    scale_ = 1.0;
}

void Figure::add_point(int x, int y)
{
    points_.push_back(QPoint(x,y));
}

void Figure::set_collor(QColor collor)
{
    collor_ = collor;
}

void Figure::paint(QPainter& painter, QVector<Figure>& triangles)
{
    painter.setPen(QPen(collor_, 4, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(collor_, Qt::SolidPattern));
    lines_.clear();
    if(points_.count()>1)
    {
    for(int i = 0; i < points_.length()-1; i++)
    {
            //painter.drawPoint(points_[i]);
        lines_.push_back(qMakePair(points_[i], points_[i+1]));
    }
        lines_.push_back(qMakePair(points_.first(), points_.back()));
    }
    if (points_.length()>2)
           for (auto &triangles: triangles) {
               QVector<QPair<QPoint, QPoint>> new_lines;
               for (auto &lines: lines_) {
                   new_lines += cyrusBeck(lines, triangles);
               }
               lines_ = new_lines;
           }
    for(int i = 0; i < lines_.count();i++)
    {
       painter.drawLine(lines_[i].first, lines_[i].second);
    }
}

void Figure::paint(QPainter &Painter, QColor &collor)
{
    Painter.setPen(QPen(collor, 4, Qt::SolidLine, Qt::FlatCap));
    Painter.setBrush(QBrush(collor, Qt::SolidPattern));
    for (auto i = 0; i < points_.length() - 1; i++) {
        Painter.drawLine(points_[i], points_[i+1]);
    }
        Painter.drawLine(points_.first(), points_.back());
}

void Figure::move(int x, int y)
{
    for(int i = 0;i<points_.count();i++)
    {
        points_[i].rx() += x;
        points_[i].ry() += y;
    }
    findCenter();
}

void Figure::rotate()
{
    qreal sin_temp = qSin(angle_);
    qreal cos_temp = qCos(angle_);
    for (int i = 0; i < points_.count(); i++)
    {
        auto x = cos_temp * (points_[i].x() - center_.x()) + sin_temp * (points_[i].y() - center_.y()) + center_.x();
        points_[i].ry() = cos_temp * (points_[i].y() - center_.y()) - sin_temp * (points_[i].x() - center_.x()) + center_.y();
        points_[i].rx() = x;
    }
}

bool Figure::isFigureOnCoordinates(int x, int y)
{
    bool result = false;
    int j = points_.length() - 1;
    for (int i = 0; i < points_.count(); i++){
        if ( (points_[i].y() < y && points_[j].y() >= y || points_[j].y() < y && points_[i].y() >= y) &&
                 (points_[i].x() + (y - points_[i].y()) / (points_[j].y() - points_[i].y()) * (points_[j].x() - points_[i].x()) < x) )
                    result = !result;
                    j = i;
        }
    return result;
}

void Figure::closeShape()
{
    findCenter();
}

QPoint Figure::getFirstPoint()
{
    return points_.first();
}

void Figure::setFirstPoint(int x, int y)
{
    points_.first().rx() = x;
    points_.first().ry() = y;
}

int Figure::getCountPoint()
{
    return points_.count();
}

bool Figure::isEmpty()
{
    if(points_.isEmpty())
        return true;
    return false;
}

void Figure::findCenter()
{
    qreal sx, sy, sL;
    sx = sy = sL = 0;
    for (int i = 0; i < points_.count() - 1; i++) {
        const QPoint &p1 = points_[i];
        QPoint p0;
        if (i == 0)
        {
            p0 = points_.back();
        }
        else{
            p0 = points_[i-1];
        }
        qreal L = qSqrt(qPow(p1.x() - p0.x(), 2) + qPow(p1.y() - p0.y(), 2));
        sx += (p1.x() + p0.x()) / 2.0 * L;
        sy += (p1.y() + p0.y()) / 2.0 * L;
        sL += L;
    }
    center_.rx() = sx / sL;
    center_.ry() = sy / sL;
}

QPoint Figure::findCenter(const QVector<QPoint> &points)
{
    qreal sx, sy, sL;
    sx = sy = sL = 0;
    for (int i = 0; i < points.count() - 1; i++) {
        const QPoint &p1 = points[i];
        QPoint p0;
        if (i == 0)
        {
            p0 = points.back();
        }
        else{
            p0 = points[i-1];
        }
        qreal L = qSqrt(qPow(p1.x() - p0.x(), 2) + qPow(p1.y() - p0.y(), 2));
        sx += (p1.x() + p0.x()) / 2.0 * L;
        sy += (p1.y() + p0.y()) / 2.0 * L;
        sL += L;
    }
    QPoint center;
    center.rx() = sx / sL;
    center.ry() = sy / sL;
    return center;
}

void Figure::setAngle(QPoint start, QPoint current)
{
    angle_ = qAtan2(current.y() - center_.y(), current.x() - center_.x()) - qAtan2(start.y() - center_.y(), start.x() - center_.x());
}

void Figure::setScale(int posX,int posY, QPoint& selectedPoint)
{
    scale_ = qSqrt(qPow(center_.x() - posX, 2) + qPow(center_.y() - posY, 2)) /
             qSqrt(qPow(center_.x() - selectedPoint.x(), 2) + qPow(center_.y() - selectedPoint.y(), 2));
}

void Figure::scale()
{
    findCenter();
    for (int i = 0; i< points_.count();i++)
    {
        points_[i].rx() = (points_[i].x() - center_.x()) * scale_ + center_.x();
        points_[i].ry() = (points_[i].y() - center_.y()) * scale_ + center_.y();
    }
}

QVector<Figure> Figure::triangulate()
{
    QVector<Figure> triangles;
    QVector<QPoint> remaining_points = points_;
    auto prev_remaining_points_len = remaining_points.length();

    while (remaining_points.length() > 3)
       {
           for (int i = 0; i < remaining_points.length(); i++) {
               auto i1 = i == 0 ? remaining_points.length() - 1: i - 1;
               auto i2 = i;
               auto i3 = (i + 1) % remaining_points.length();
               QVector<QPoint> p;
               p.append(remaining_points[i1]);
               p.append(remaining_points[i2]);
               p.append(remaining_points[i3]);
               auto angle = qAtan2(p[2].y() - p[1].y(), p[2].x() - p[1].x()) - qAtan2(p[0].y() - p[1].y(), p[0].x() - p[1].x());
               if (qFabs(angle) >= M_PI) continue;
               Figure triangleCandidate;
               triangleCandidate.points_ = p;
               auto cont_f = false;
               for (auto l = 0; l < remaining_points.length(); l++) {
                   if (l == i1 || l == i2 || l == i3) continue;
                   if (triangleCandidate.isFigureOnCoordinates(remaining_points[l].x(),remaining_points[l].y())) cont_f = true;
               }
               if (cont_f)
                   continue;
               triangles.append(triangleCandidate);
               remaining_points.remove(i);
               break;
           }
           if (remaining_points.length() == prev_remaining_points_len)
               break;
           else
               prev_remaining_points_len = remaining_points.length();
       }
       Figure temp;
       temp.points_ = {remaining_points[0], remaining_points[1], remaining_points[2]};
       triangles.append(temp);
       for (int i = 0; i < triangles.count(); i++) {
           triangles[i].sortPointsClock();
       }
       return triangles;
}

void Figure::sortPointsClock()
{
    std::sort(points_.begin(), points_.end(), std::bind(Figure::compare_points_of_center, std::placeholders::_1, std::placeholders::_2, findCenter(points_)));
}

bool Figure::compare_points_of_center(const QPoint &p1, const QPoint &p2, const QPoint &center)
{
    double angle1 = qAtan2(p1.y() - center.y(), p1.x() - center.x());
    double angle2 = qAtan2(p2.y() - center.y(), p2.x() - center.x());
    return angle1 < angle2;
}

void Figure::paintTriangles(QPainter& painter)
{
    for (auto &i: triangulate()) {
            i.paint(painter, collor_);
    }
}

QVector<QPair<QPoint, QPoint> > Figure::cyrusBeck(const QPair<QPoint, QPoint> &line, const Figure &shape)
{
    auto d = line.first - line.second;
    QVector<QPoint> normals;
    auto shapePoints = shape.points_;
    for (auto i = 0; i < shapePoints.length(); i++) {
        auto s = shapePoints[(i + 1) % shapePoints.length()];
        auto e = shapePoints[i];
        auto x = e.y() - s.y();
        auto y = s.x() - e.x();
        normals.append(QPoint(x, y));
    }
    double tE = 0;
    double tL = 1;
    for (auto i = 0; i < normals.length(); i++) {
        auto dot_prod = normals[i].x()*d.x() + normals[i].y()*d.y();
        if (dot_prod != 0){
            auto diff = shapePoints[i] - line.first;
            auto t = (normals[i].x()*diff.x() + normals[i].y()*diff.y()) / (1.0 * -1 * dot_prod);
            if (dot_prod < 0) tE = qMax(tE, t);
            else tL = qMin(tL, t);
        }else{
            auto a = shapePoints[i];
            auto b = shapePoints[(i + 1) % shapePoints.length()];
            auto c = line.first;
            if ((b.x() - a.x()) * (c.y() - a.y()) - (b.y() - a.y()) * (c.x() - a.x()) < 0) {
                tE = 1;
                tL = -1;
            }
        }
    }
    if (tE > tL)
        return QVector<QPair<QPoint, QPoint>>({line});

    auto p1 = line.first + (line.second - line.first) * tE;
    auto p2 = line.first + (line.second - line.first) * tL;

    if (tE == 0 && tL == 1) {
        return QVector<QPair<QPoint, QPoint>>();
    }
    if (tE == 0){
        return QVector<QPair<QPoint, QPoint>>({qMakePair(p2, line.second)});
    } else if (tL == 1) {
        return QVector<QPair<QPoint, QPoint>>({qMakePair(line.first, p1)});
    } else {
        return QVector<QPair<QPoint, QPoint>>({qMakePair(line.first, p1), qMakePair(p2, line.second)});
    }
}

