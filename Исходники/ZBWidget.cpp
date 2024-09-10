ZBWidget::Matrix4 ZBWidget::lookAt(float eye_x, float eye_y, float eye_z,
                                   float center_x, float center_y, float center_z,
                                   float up_x, float up_y, float up_z)
{
  Vector3 eye(eye_x, eye_y, eye_z);
  Vector3 center(center_x, center_y, center_z);
  Vector3 up(up_x, up_y, up_z);
  Vector3 f = (center-eye).normalized();
  Vector3 s = f.cross(up).normalized();
  Vector3 u = s.cross(f).normalized();

  Matrix4 result(Matrix4::Identity());
  result(0, 0) = s.x();
  result(0, 1) = s.y();
  result(0, 2) = s.z();
  result(1, 0) = u.x();
  result(1, 1) = u.y();
  result(1, 2) = u.z();
  result(2, 0) = -f.x();
  result(2, 1) = -f.y();
  result(2, 2) = -f.z();
  result(0, 3) = -s.dot(eye);
  result(1, 3) = -u.dot(eye);
  result(2, 3) = f.dot(eye);
  return result;
}