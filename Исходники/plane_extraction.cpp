//TODO: move to semantics
void
PlaneExtraction::findClosestTable(std::vector<pcl::PointCloud<Point>, Eigen::aligned_allocator<pcl::PointCloud<Point> > >& v_cloud_hull,
                                  std::vector<pcl::ModelCoefficients>& v_coefficients_plane,
                                  Eigen::Vector3f& robot_pose,
                                  unsigned int& idx)
{
  std::vector<unsigned int> table_candidates;
  for(unsigned int i=0; i<v_cloud_hull.size(); i++)
  {
    //if(fabs(v_coefficients_plane[i].values[3])>0.5 && fabs(v_coefficients_plane[i].values[3])<1.2)
    table_candidates.push_back(i);
  }
  if(table_candidates.size()>0)
  {
    for(unsigned int i=0; i<table_candidates.size(); i++)
    {
      double d_min = 1000;
      double d = d_min;
      Eigen::Vector4f centroid;
      pcl::compute3DCentroid(v_cloud_hull[i], centroid);
      //for(unsigned int j=0; j<v_cloud_hull[i].size(); j++)
      //{
      //  Eigen::Vector3f p = v_cloud_hull[i].points[j].getVector3fMap();
      //  d += fabs((p-robot_pose).norm());
      //}
      //d /= v_cloud_hull[i].size();
      Eigen::Vector3f centroid3 = centroid.head(3);
      d = fabs((centroid3-robot_pose).norm());
      ROS_INFO("d: %f", d);
      if(d<d_min)
      {
        d_min = d;
        idx = table_candidates[i];
      }
    }
  }
}