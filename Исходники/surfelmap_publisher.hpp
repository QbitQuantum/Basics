void SurfelMapPublisher::publishSurfelMarkers(const boost::shared_ptr<MapType>& map)
{
  if (m_markerPublisher.getNumSubscribers() == 0)
    return;

  unsigned int markerId = 0;
  std::vector<float> cellSizes;
  typename MapType::AlignedCellVectorVector occupiedCells;
  std::vector<std::vector<pcl::PointXYZ>> occupiedCellsCenters;

  int levels = map->getLevels();
  for (unsigned int i = 0; i < m_lastSurfelMarkerCount; ++i)
  {
    for (unsigned int l = 0; l < levels; l++)
    {
      visualization_msgs::Marker marker;
      marker.header.frame_id = map->getFrameId();
      marker.header.stamp = map->getLastUpdateTimestamp();
      marker.ns = boost::lexical_cast<std::string>(l);
      marker.id = i;
      marker.type = marker.SPHERE;
      marker.action = marker.DELETE;
      m_markerPublisher.publish(marker);
    }
  }

  for (unsigned int l = 0; l < levels; l++)
  {
    cellSizes.push_back(map->getCellSize(l));

    typename MapType::AlignedCellVector occupiedCellsTemp;
    std::vector<pcl::PointXYZ> occupiedCellsCentersTemp;
    map->getOccupiedCells(occupiedCellsTemp, l);
    map->getOccupiedCells(occupiedCellsCentersTemp, l);

    occupiedCells.push_back(occupiedCellsTemp);
    occupiedCellsCenters.push_back(occupiedCellsCentersTemp);
  }

  for (unsigned int l = 0; l < cellSizes.size(); l++)
  {
    float cellSize = cellSizes[l];

    for (size_t i = 0; i < occupiedCells[l].size(); i++)
    {
      const mrs_laser_maps::Surfel& surfel = occupiedCells[l][i].surfel_;

      //				if (surfel.num_points_ < 15 )
      //					continue;
      //
      //				if ( surfel.unevaluated_ ) {
      //					ROS_ERROR("not unevaluated surfel");
      //					continue;
      //				}

      Eigen::Matrix<double, 3, 3> cov = surfel.cov_.block(0, 0, 3, 3);
      Eigen::EigenSolver<Eigen::Matrix3d> solver(cov);
      Eigen::Matrix<double, 3, 3> eigenvectors = solver.eigenvectors().real();
      //				double eigenvalues[3];
      Eigen::Matrix<double, 3, 1> eigenvalues = solver.eigenvalues().real();
      //				for(int j = 0; j < 3; ++j) {
      //					Eigen::Matrix<double, 3, 1> mult = cov * eigenvectors.col(j);
      //					eigenvalues[j] = mult(0,0) / eigenvectors.col(j)(0);
      //				}
      if (eigenvectors.determinant() < 0)
      {
        eigenvectors.col(0)(0) = -eigenvectors.col(0)(0);
        eigenvectors.col(0)(1) = -eigenvectors.col(0)(1);
        eigenvectors.col(0)(2) = -eigenvectors.col(0)(2);
      }
      Eigen::Quaternion<double> q = Eigen::Quaternion<double>(eigenvectors);
      visualization_msgs::Marker marker;
      marker.header.frame_id = map->getFrameId();
      marker.header.stamp = map->getLastUpdateTimestamp();
      marker.ns = boost::lexical_cast<std::string>(l);
      marker.id = markerId++;
      marker.type = marker.SPHERE;
      marker.action = marker.ADD;
      marker.pose.position.x = occupiedCellsCenters[l][i].x - cellSize / 2 + surfel.mean_(0);
      marker.pose.position.y = occupiedCellsCenters[l][i].y - cellSize / 2 + surfel.mean_(1);
      marker.pose.position.z = occupiedCellsCenters[l][i].z - cellSize / 2 + surfel.mean_(2);
      marker.pose.orientation.w = q.w();
      marker.pose.orientation.x = q.x();
      marker.pose.orientation.y = q.y();
      marker.pose.orientation.z = q.z();
      marker.scale.x = std::max(sqrt(eigenvalues[0]) * 3, 0.01);
      marker.scale.y = std::max(sqrt(eigenvalues[1]) * 3, 0.01);
      marker.scale.z = std::max(sqrt(eigenvalues[2]) * 3, 0.01);
      marker.color.a = 1.0;

      double dot = surfel.normal_.dot(Eigen::Vector3d(0., 0., 1.));
      if (surfel.normal_.norm() > 1e-10)
        dot /= surfel.normal_.norm();
      double angle = acos(fabs(dot));
      double angle_normalized = 2. * angle / M_PI;
      marker.color.r = ColorMapJet::red(angle_normalized);  // fabs(surfel.normal_(0));
      marker.color.g = ColorMapJet::green(angle_normalized);
      marker.color.b = ColorMapJet::blue(angle_normalized);

      m_markerPublisher.publish(marker);
    }
  }
  m_lastSurfelMarkerCount = markerId;
}