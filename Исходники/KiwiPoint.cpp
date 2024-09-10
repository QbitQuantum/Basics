 Point Point::nearest(Point const& start, Point const& ctrl, Point const& end) const noexcept
 {
     const Point A = ctrl - start;
     const Point B = start - ctrl * 2 - end;
     const Point C = start - *this;
     double sol1, sol2, sol3;
     
     const ulong nresult = solve(B.length(), 3 * A.dot(B), 2 * A.length() + C.dot(B), A.dot(C), sol1, sol2, sol3);
     if(nresult)
     {
         Point pt = fromLine(start, ctrl, end, sol1);
         double dist = distance(pt);
         if(nresult > 1)
         {
             const Point pt2 = fromLine(start, ctrl, end, sol2);
             const double dist2 = distance(pt2);
             if(dist2 < dist)
             {
                 dist = dist2;
                 pt = pt2;
             }
         }
         if(nresult > 2)
         {
             const Point pt2 = fromLine(start, ctrl, end, sol3);
             const double dist2 = distance(pt2);
             if(dist2 < dist)
             {
                 dist  = dist2;
                 pt = pt2;
             }
         }
         return pt;
     }
     else
     {
         return (distance(start) < distance(end)) ? start : end;
     }
 }