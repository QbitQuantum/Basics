 RUNEMATH_API bool Intersect(const Sphere3<T> &s1, const Sphere3<T> &s2, Vec3<T> &point)
 {
     if (Intersect(s1, s2))
     {
         Vec3<T> dir = s1.pos - s2.pos;
         dir.Normalize();
         point = s2.pos + dir * s2.radius;
         return true;
     }
     return false;
 }