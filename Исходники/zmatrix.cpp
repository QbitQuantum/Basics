vector<Vector3d> getAxes(const Vector3d &r1,const Vector3d &r2,const Vector3d &r3)
{
  vector<Vector3d> l0;
  Vector3d i = (r3 - r2).normalized(), r21 = r1 - r2;
  Vector3d e = (r21 - (r21.dot(i) * i)).normalized();
  l0.push_back(i); l0.push_back(e); l0.push_back(i.cross(e));
  return l0;
}