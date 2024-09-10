 // error function for distance cost
 double Con2dP2::calcErrDist(const Node2d &nd0, const Node2d &nd1)
   { 
     Vector2d derr = nd0.w2n * nd1.trans - tmean;
     return derr.dot(derr);
   }