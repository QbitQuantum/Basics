Point PointCloudTransform::worldToImage(const Point &p)
{
  //test if point is lying in view frustrum
  float l = p.dot(leftClippingNormal);  // distance to plane
  float r = p.dot(rightClippingNormal);
  if(l * r > 0.0f) { return Point(POINT_INVALID, POINT_INVALID); } // outside frustrum
  float t = p.dot(topClippingNormal);
  float b = p.dot(bottomClippingNormal);
  if(t * b > 0.0f) { return Point(POINT_INVALID, POINT_INVALID); } // outside frustrom

  float x_ = p.x / p.z;
  float y_ = p.y / p.z;

  float r2 = x_ * x_ + y_ * y_;
  float r4 = r2 * r2;
  float r6 = r2 * r4;

  float xss = x_ * (1.0f + k1 * r2 + k2 * r4 + k3 * r6) + 2.0f * p1 * x_ * y_ + p2 * (r2 + 2.0f * x_ * x_);
  float yss = y_ * (1.0f + k1 * r2 + k2 * r4 + k3 * r6) + p1 * (r2 + 2.0f * y_ * y_) + 2.0f * p2 * x_ * y_;

  return Point((float)fx * xss + (float)cx - left, (float)fy * yss + (float)cy - top);
}