template<typename Point> void
TableObjectCluster<Point>::calculateBoundingBox(
  const PointCloudPtr& cloud,
  const pcl::PointIndices& indices,
  const Eigen::Vector3f& plane_normal,
  const Eigen::Vector3f& plane_point,
  Eigen::Vector3f& position,
  Eigen::Quaternion<float>& orientation,
  Eigen::Vector3f& size)
{
  // transform to table coordinate frame and project points on X-Y, save max height
  Eigen::Affine3f tf;
  pcl::getTransformationFromTwoUnitVectorsAndOrigin(plane_normal.unitOrthogonal(), plane_normal, plane_point, tf);
  pcl::PointCloud<pcl::PointXYZ>::Ptr pc2d(new pcl::PointCloud<pcl::PointXYZ>);
  float height = 0.0;
  for(std::vector<int>::const_iterator it=indices.indices.begin(); it != indices.indices.end(); ++it)
  {
    Eigen::Vector3f tmp = tf * (*cloud)[*it].getVector3fMap();
    height = std::max<float>(height, fabs(tmp(2)));
    pc2d->push_back(pcl::PointXYZ(tmp(0),tmp(1),0.0));
  }

  // create convex hull of projected points
  #ifdef PCL_MINOR_VERSION >= 6
  pcl::PointCloud<pcl::PointXYZ>::Ptr conv_hull(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::ConvexHull<pcl::PointXYZ> chull;
  chull.setDimension(2);
  chull.setInputCloud(pc2d);
  chull.reconstruct(*conv_hull);
  #endif

  /*for(int i=0; i<conv_hull->size(); ++i)
    std::cout << (*conv_hull)[i].x << "," << (*conv_hull)[i].y << std::endl;*/

  // find the minimal bounding rectangle in 2D and table coordinates
  Eigen::Vector2f p1, p2, p3;
  cob_3d_mapping::MinimalRectangle2D mr2d;
  mr2d.setConvexHull(conv_hull->points);
  mr2d.rotatingCalipers(p2, p1, p3);
  /*std::cout << "BB: \n" << p1[0] << "," << p1[1] <<"\n"
            << p2[0] << "," << p2[1] <<"\n"
            << p3[0] << "," << p3[1] <<"\n ---" << std::endl;*/

  // compute center of rectangle
  position[0] = 0.5f*(p1[0] + p3[0]);
  position[1] = 0.5f*(p1[1] + p3[1]);
  position[2] = 0.0f;
  // transform back
  Eigen::Affine3f inv_tf = tf.inverse();
  position = inv_tf * position;
  // set size of bounding box
  float norm_1 = (p3-p2).norm();
  float norm_2 = (p1-p2).norm();
  // BoundingBox coordinates: X:= main direction, Z:= table normal
  Eigen::Vector3f direction; // y direction
  if (norm_1 < norm_2)
  {
    direction = Eigen::Vector3f(p3[0]-p2[0], p3[1]-p2[1], 0) / (norm_1);
    size[0] = norm_2 * 0.5f;
    size[1] = norm_1 * 0.5f;
  }
  else
  {
    direction = Eigen::Vector3f(p1[0]-p2[0], p1[1]-p2[1], 0) / (norm_2);
    size[0] = norm_1 * 0.5f;
    size[1] = norm_2 * 0.5f;
  }
  size[2] = -height;


  direction = inv_tf.rotation() * direction;
  orientation = pcl::getTransformationFromTwoUnitVectors(direction, plane_normal).rotation(); // (y, z-direction)

  return;
  Eigen::Matrix3f M = Eigen::Matrix3f::Identity() - plane_normal * plane_normal.transpose();
  Eigen::Vector3f xn = M * Eigen::Vector3f::UnitX(); // X-axis project on normal
  Eigen::Vector3f xxn = M * direction;
  float cos_phi = acos(xn.normalized().dot(xxn.normalized())); // angle between xn and main direction
  cos_phi = cos(0.5f * cos_phi);
  float sin_phi = sqrt(1.0f-cos_phi*cos_phi);
  //orientation.w() = cos_phi;
  //orientation.x() = sin_phi * plane_normal(0);
  //orientation.y() = sin_phi * plane_normal(1);
  //orientation.z() = sin_phi * plane_normal(2);
}