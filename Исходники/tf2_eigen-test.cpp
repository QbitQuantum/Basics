TEST(TfEigen, ConvertAffine3d)
{
  const Eigen::Affine3d v(Eigen::Translation3d(1,2,3) * Eigen::AngleAxis<double>(1, Eigen::Vector3d::UnitX()));

  Eigen::Affine3d v1;
  geometry_msgs::Pose p1;
  tf2::convert(v, p1);
  tf2::convert(p1, v1);

  EXPECT_EQ(v.translation(), v1.translation());
  EXPECT_EQ(v.rotation(), v1.rotation());
}