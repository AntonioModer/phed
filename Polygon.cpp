/* 
 * File:   Polygon.cpp
 * Author: mark
 * 
 * Created on August 26, 2009, 1:07 PM
 */

#include <algorithm>
#include <limits>
#include <qt4/QtCore/qline.h>
#include <Box2D/Box2D.h>
#include "Polygon.h"

Polygon::Polygon(): QPolygonF() {
}

Polygon::Polygon(int size): QPolygonF(size) {
}

Polygon::Polygon(const QPolygonF & polygon): QPolygonF(polygon) {
}

Polygon::Polygon(const QVector<QPointF> & points): QPolygonF(points) {
}

Polygon::Polygon(const QRectF & rectangle): QPolygonF(rectangle) {
}

Polygon::Polygon(const QPolygon & polygon): QPolygonF(polygon) {
}

const QPointF& Polygon::at(int i) const {
    const int s = size();
    return(*this)[i < 0 ? s - (-i % s) : i % s];
}

Polygon::Orientation Polygon::orientation() const {
    int br = 0;
    for(int i = 1; i < size(); ++i) {
        if((*this)[i].y() < (*this)[br].y() || ((*this)[i].y() == (*this)[br].y() && (*this)[i].x() > (*this)[br].x())) {
            br = i;
        }
    }
    if(right(br)) return CW;
    else return CCW;
}

Polygon Polygon::ccw() const {
    Polygon ccw(size());
    if(orientation() == CW) std::reverse_copy(begin(), end(), ccw.begin());
    else std::copy(begin(), end(), ccw.begin());
    return ccw;
}

Polygon Polygon::copy(int i, int j) const {
    Polygon p;
    while(j < i) j += size();
    for(; i <= j; ++i) {
        p.append(at(i));
    }
    return p;
}

QList<Polygon> Polygon::decomp() const {
    QList<Polygon> list;
    qreal d, dist1, dist2;
    QPointF ip, ip1, ip2; // intersection points
    int ind1, ind2;
    Polygon poly1, poly2;

    for(int i = 0; i < size(); ++i) {
        if(reflex(i)) {
            dist1 = dist2 = std::numeric_limits<qreal>::max();
            for(int j = 0; j < size(); ++j) {
                if(left(at(i - 1), at(i), at(j)) && rightOn(at(i - 1), at(i), at(j - 1))) { // if ray (i-1)->(i) intersects with edge (j, j-1)
                    QLineF(at(i - 1), at(i)).intersect(QLineF(at(j), at(j - 1)), &ip);
                    if(right(at(i + 1), at(i), ip)) { // intersection point isn't caused by backwards ray
                        d = sqdist(at(i), ip);
                        if(d < dist1) { // take the closest intersection so we know it isn't blocked by another edge
                            dist1 = d;
                            ind1 = j;
                            ip1 = ip;
                        }
                    }
                }
                if(left(at(i + 1), at(i), at(j + 1)) && rightOn(at(i + 1), at(i), at(j))) { // if ray (i+1)->(i) intersects with edge (j+1, j)
                    QLineF(at(i + 1), at(i)).intersect(QLineF(at(j), at(j + 1)), &ip);
                    if(left(at(i - 1), at(i), ip)) {
                        d = sqdist(at(i), ip);
                        if(d < dist2) {
                            dist2 = d;
                            ind2 = j;
                            ip2 = ip;
                        }
                    }
                }
            }
            if(ind1 == (ind2 + 1) % size()) { // no vertices in range
                QPointF sp((ip1 + ip2) / 2);
                poly1 = copy(i, ind2);
                poly1.append(sp);
                poly2 = copy(ind1, i);
                poly2.append(sp);
            } else {
                double highestScore = 0, bestIndex = ind1, score;
                while(ind2 < ind1) ind2 += size();
                for(int j = ind1; j <= ind2; ++j) {
                    if(canSee(i, j)) {
                        score = 1 / (sqdist(at(i), at(j)) + 1);
                        if(reflex(j)) {
                            if(rightOn(at(j - 1), at(j), at(i)) && leftOn(at(j + 1), at(j), at(i))) {
                                score += 3;
                            } else {
                                score += 2;
                            }
                        } else {
                            score += 1;
                        }
                        if(score > highestScore) {
                            bestIndex = j;
                            highestScore = score;
                        }
                    }
                }
                poly1 = copy(i, bestIndex);
                poly2 = copy(bestIndex, i);
            }
            list += poly1.decomp();
            list += poly2.decomp();
            return list;
        }
    }
    // polygon is already convex
    if(size() > b2_maxPolygonVertices) {
        poly1 = copy(0, size() / 2);
        poly2 = copy(size() / 2, 0);
        list += poly1.decomp();
        list += poly2.decomp();
    } else list.append(*this);
    return list;
}

bool Polygon::canSee(int i, int j) const {
    if(reflex(i)) {
        if(leftOn(at(i), at(i - 1), at(j)) && rightOn(at(i), at(i + 1), at(j))) return false;
    } else {
        if(rightOn(at(i), at(i + 1), at(j)) || leftOn(at(i), at(i - 1), at(j))) return false;
    }
    if(reflex(j)) {
        if(leftOn(at(j), at(j - 1), at(i)) && rightOn(at(j), at(j + 1), at(i))) return false;
    } else {
        if(rightOn(at(j), at(j + 1), at(i)) || leftOn(at(j), at(j - 1), at(i))) return false;
    }
    for(int k = 0; k < size(); ++k) {
        if((k + 1) % size() == i || k == i || (k + 1) % size() == j || k == j) {
            continue; // ignore incident edges
        }
        if(QLineF(at(i), at(j)).intersect(QLineF(at(k), at(k + 1)), NULL) == QLineF::BoundedIntersection) {
            return false;
        }
    }
    return true;
}

bool Polygon::reflex(int i) const {
    return right(i);
}

bool Polygon::left(int i) const {
    return left(at(i - 1), at(i), at(i + 1));
}

bool Polygon::leftOn(int i) const {
    return leftOn(at(i - 1), at(i), at(i + 1));
}

bool Polygon::right(int i) const {
    return right(at(i - 1), at(i), at(i + 1));
}

bool Polygon::rightOn(int i) const {
    return rightOn(at(i - 1), at(i), at(i + 1));
}

bool Polygon::collinear(int i) const {
    return collinear(at(i - 1), at(i), at(i + 1));
}

qreal Polygon::area(const QPointF &a, const QPointF &b, const QPointF &c) {
    return((b.x() - a.x())*(c.y() - a.y()))-((c.x() - a.x())*(b.y() - a.y()));
}

bool Polygon::left(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) > 0;
}

bool Polygon::leftOn(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) >= 0;
}

bool Polygon::right(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) < 0;
}

bool Polygon::rightOn(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) <= 0;
}

bool Polygon::collinear(const QPointF &a, const QPointF &b, const QPointF &c) {
    return area(a, b, c) == 0;
}

qreal Polygon::sqdist(const QPointF &a, const QPointF &b) {
    qreal dx = b.x() - a.x();
    qreal dy = b.y() - a.y();
    return dx * dx + dy * dy;
}