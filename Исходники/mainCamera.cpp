void MainCamera::lookToTarget() {
  Vec3f z = getForward() / getForward().length();

  Vec3f b = up_.cross(z);
  Vec3f x = b / b.length();

  Vec3f y = z.cross(x);

  Eigen::Matrix4f R;
  R << x.x,   x.y,  x.z, 0.0f,
       y.x,   y.y,  y.z, 0.0f,
       z.x,   z.y,  z.z, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f;

  Eigen::Matrix4f T;
  T << 1.0f, 0.0f, 0.0f, -pos_.x,
       0.0f, 1.0f, 0.0f, -pos_.y,
       0.0f, 0.0f, 1.0f, -pos_.z,
       0.0f, 0.0f, 0.0f,    1.0f;

  Eigen::Matrix4f m = R * T;
  glMultMatrixf(m.data());
}