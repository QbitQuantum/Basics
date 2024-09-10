/* ************************************************************************* */
double PoseRTV::range(const PoseRTV& other,
    OptionalJacobian<1,9> H1, OptionalJacobian<1,9> H2) const {
  Matrix36 D_t1_pose, D_t2_other;
  const Point3 t1 = pose().translation(H1 ? &D_t1_pose : 0);
  const Point3 t2 = other.pose().translation(H2 ? &D_t2_other : 0);
  Matrix13 D_d_t1, D_d_t2;
  double d = t1.distance(t2, H1 ? &D_d_t1 : 0, H2 ? &D_d_t2 : 0);
  if (H1) *H1 << D_d_t1 * D_t1_pose, 0,0,0;
  if (H2) *H2 << D_d_t2 * D_t2_other, 0,0,0;
  return d;
}