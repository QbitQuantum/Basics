 bool Intersects(const Convex& other, Point& intersection) const override
 {
     return other.Intersects(*this, intersection);
 }