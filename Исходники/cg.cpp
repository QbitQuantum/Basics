 int side(const Vector2D& v) const {
     // on line: 0, left side: 1, right side: 0
     double tmp = dir.cross(v-p0);
     return tmp == 0? 0 : (tmp > 0? 1 : -1);
 }