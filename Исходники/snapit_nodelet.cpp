  bool SnapIt::checkPointInsidePlane(EigenVector3fVector &plane_points,
                                     Eigen::Vector3f normal,
                                     Eigen::Vector3f point)
  {
    if (isnan(point[0]) || isnan(point[1]) || isnan(point[2])) {
      return false;
    }
    for (size_t i = 0; i < plane_points.size(); i++) {
      Eigen::Vector3f B;
      Eigen::Vector3f O = plane_points[i];

      if (i == (plane_points.size() - 1)) {
        B = plane_points[0];
      }
      else {
        B = plane_points[i + 1];
      }
      Eigen::Vector3f OB = B - O;
      Eigen::Vector3f OP = point - O;
      if ((OB.cross(OP)).dot(normal) < 0) {
        return false;
      }
    }

    return true;
  }