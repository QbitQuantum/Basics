void motion3(Eigen::Matrix3f &rot, Eigen::Vector3f &tr)
{
  Eigen::Vector3f n;
  n(0) = gen_random_float(-1,1);
  n(1) = gen_random_float(-1,1);
  n(2) = gen_random_float(-1,1);
  n.normalize();
  Eigen::AngleAxisf aa(gen_random_float(-0.02f,0.05f),n);
  rot = aa.toRotationMatrix();
  tr.fill(0);
}