template<typename PointInT, typename PointNT, typename PointOutT> float
pcl::BOARDLocalReferenceFrameEstimation<PointInT, PointNT, PointOutT>::getAngleBetweenUnitVectors (
                                                                                                   Eigen::Vector3f const &v1,
                                                                                                   Eigen::Vector3f const &v2,
                                                                                                   Eigen::Vector3f const &axis)
{
  Eigen::Vector3f angle_orientation;
  angle_orientation = v1.cross (v2);
  float angle_radians = acosf (std::max (-1.0f, std::min (1.0f, v1.dot (v2))));

  angle_radians = angle_orientation.dot (axis) < 0.f ? (2 * static_cast<float> (M_PI) - angle_radians) : angle_radians;

  return (angle_radians);
}