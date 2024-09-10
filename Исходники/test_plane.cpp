 /** The computed distance is perfect in that case
  * @param p_j the point to compute its distance to
  * @return
  */
 float distance(const Vec3f& p_j) const
 {
   return std::abs(float(p_j.dot(n_) + d_));
 }