 /**
  * The GARS precision required to meet a given geographic resolution.
  *
  * @param[in] res the minimum of resolution in latitude and longitude
  *   (degrees).
  * @return GARS precision.
  *
  * The returned length is in the range [0, 2].
  **********************************************************************/
 static int Precision(real res) {
   using std::abs; res = abs(res);
   for (int prec = 0; prec < maxprec_; ++prec)
     if (Resolution(prec) <= res)
       return prec;
   return maxprec_;
 }