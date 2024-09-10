 Plane(const Point &p1, const Point &p2, const Point &p3) {
     Point normal = (p2 - p1) * (p3 - p1);
     normal.normalize();
     if (cmp(normal.x, 0) < 0 or
         cmp(normal.x, 0) == 0 and cmp(normal.y, 0) < 0 or
         cmp(normal.x, 0) == 0 and cmp(normal.y, 0) == 0 and cmp(normal.z, 0) < 0) {
             normal = -normal;
     }
     
     a = normal.x, b = normal.y, c = normal.z;
     d = -(normal ^ p1);
     assert(cmp(d, -(normal ^ p2)) == 0);
     assert(cmp(d, -(normal ^ p3)) == 0);
 }