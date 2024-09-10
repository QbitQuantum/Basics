double Point::xyDistanceToLine(const Point &p1, const Point &p2) const
{
    // see for example
    // http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
    if ((p1.x == p2.x) && (p1.y == p2.y)) {// no line in xy plane
        std::cout << "point.cpp: xyDistanceToLine ERROR!: can't calculate distance from \n";
        std::cout << "point.cpp: xyDistanceToLine ERROR!: *this ="<<*this <<" to line through\n";
        std::cout << "point.cpp: xyDistanceToLine ERROR!: p1="<<p1<<" and \n";
        std::cout << "point.cpp: xyDistanceToLine ERROR!: p2="<<p2<< "\n";
        std::cout << "point.cpp: xyDistanceToLine ERROR!: in the xy-plane\n";
        return -1;
    }
    else {
        Point v = Point(p2.y-p1.y, -(p2.x-p1.x), 0 );
        v.normalize();
        Point r = Point(p1.x - x, p1.y - y, 0);
        return fabs( v.dot(r));
    }
}