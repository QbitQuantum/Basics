 Rectf grown(float border) const
 {
   return Rectf(p1.x - border, p1.y - border,
                p2.x + border, p2.y + border);
 }