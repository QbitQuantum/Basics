bool insideConvexPolygon(const Vector &point, const Vector *corners, Index nCorners, const Vector &normal) {

   // project into 2D and transform point into origin
   Index max = 0;
   normal.cwiseAbs().maxCoeff(&max);
   int c1=0, c2=1;
   if (max == 0) {
      c1 = 1;
      c2 = 2;
   } else if (max == 1) {
      c1 = 0;
      c2 = 2;
   }
   Vector2 point2;
   point2 << point[c1], point[c2];
   std::vector<Vector2> corners2(nCorners);
   for (Index i=0; i<nCorners; ++i) {
      corners2[i] << corners[i][c1], corners[i][c2];
      corners2[i] -= point2;
   }

   // check whether edges pass the origin at the same side
   Scalar sign(0);
   for (Index i=0; i<nCorners; ++i) {
      Vector2 n = corners2[(i+1)%nCorners] - corners2[i];
      std::swap(n[0],n[1]);
      n[0] *= -1;
      if (sign==0) {
          sign = n.dot(corners2[i]);
          if (std::abs(sign) < 1e-5)
              sign = 0;
      } else if (n.dot(corners2[i])*sign < 0) {
#ifdef INTERPOL_DEBUG
         std::cerr << "outside: normal: " << normal.transpose() << ", point: " << point.transpose() << ", p2: " << point2.transpose() << std::endl;
#endif
         return false;
      }
   }

#ifdef INTERPOL_DEBUG
   std::cerr << "inside: normal: " << normal.transpose() << ", point: " << point.transpose() << ", p2: " << point2.transpose() << std::endl;
#endif

   return true;
}