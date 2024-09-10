 void Path::addPieChart(Point const& center, const Point& radius, const double start, const double end) noexcept
 {
     const vector<Point> points = BezierCubic::fromArc(center, radius, start, end);
     moveTo(center);
     lineTo(points[0]);
     for(vector<Point>::size_type i = 1; i < points.size(); i++)
     {
         addNode(Node(points[i], Cubic));
     }
     lineTo(center);
     close();
 }