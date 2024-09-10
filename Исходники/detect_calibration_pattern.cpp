int PatternDetector::detectPattern(cv::Mat& image_in, Eigen::Vector3f& translation, Eigen::Quaternionf& orientation,
                                   cv::Mat& image_out)
{
  translation.setZero();
  orientation.setIdentity();

  bool found = false;

  observation_pts_t observation_points;

  switch (pattern_type)
  {
    case ASYMMETRIC_CIRCLES_GRID:
      found = cv::findCirclesGrid(image_in, grid_size, observation_points,
                                  cv::CALIB_CB_ASYMMETRIC_GRID | cv::CALIB_CB_CLUSTERING);
      break;
    case CHESSBOARD:
      found = cv::findChessboardCorners(image_in, grid_size, observation_points, cv::CALIB_CB_ADAPTIVE_THRESH);
      break;
    case CIRCLES_GRID:
      found = cv::findCirclesGrid(image_in, grid_size, observation_points, cv::CALIB_CB_SYMMETRIC_GRID);
      break;
  }

  if (found)
  {
    // Do subpixel ONLY IF THE PATTERN IS A CHESSBOARD
    if (pattern_type == CHESSBOARD)
    {
      cv::cornerSubPix(image_in, observation_points, cv::Size(5, 5), cv::Size(-1, -1),
                       cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 100, 0.01));
    }

    cv::solvePnP(cv::Mat(ideal_points), cv::Mat(observation_points), K, D, rvec, tvec, false);
    cv::Rodrigues(rvec, R); //take the 3x1 rotation representation to a 3x3 rotation matrix.

    cv::drawChessboardCorners(image_out, grid_size, cv::Mat(observation_points), found);

    convertCVtoEigen(tvec, R, translation, orientation);
  }

  return found;
}