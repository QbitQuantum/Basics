 void PathSerializer::WritePoint(const Point2F& point) {
     result << point.GetX() << ' ' << point.GetY() << ' ';
 }