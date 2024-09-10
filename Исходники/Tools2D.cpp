void Vector2D::ProjToLine (const Vector2D &rclPt, const Vector2D &rclLine)
{
  double l  = rclLine.Length();
  double t1 = (rclPt * rclLine) / l;
  Vector2D clNormal = rclLine;
  clNormal.Normalize();
  clNormal.Scale(t1);  
  *this = clNormal;
}