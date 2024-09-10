 Vec3f snapLength(const Vec3f p, float t) const
 {
     if (p.length() == 0.0f)
         return Vec3f(0.0f);
     else
         return p.normalized()*snapToGrid(p.length(), t);
 }