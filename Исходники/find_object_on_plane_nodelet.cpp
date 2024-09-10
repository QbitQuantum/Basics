  void FindObjectOnPlane::generateAngles(
    const cv::Mat& blob_image, const cv::Point2f& test_point,
    std::vector<double>& angles,
    std::vector<double>& max_x,
    std::vector<double>& max_y,
    const image_geometry::PinholeCameraModel& model,
    const jsk_recognition_utils::Plane::Ptr& plane)
  {
    angles.clear();
    const double angle_step = 3;
    std::vector<cv::Point> indices;
    for (int j = 0; j < blob_image.rows; j++) {
        for (int i = 0; i < blob_image.cols; i++) {
          if (blob_image.at<uchar>(j, i) != 0) { // need to check
            indices.push_back(cv::Point(i, j));
          }
        }
    }
    for (double angle = -180; angle < 180; angle += angle_step) {
      Eigen::Vector2f ux(cos(angle/180*M_PI), sin(angle/180*M_PI));
      //Eigen::Vector2f uy(sin(angle/180*M_PI), -cos(angle/180*M_PI));
      cv::Point2d uy_end = getUyEnd(test_point, cv::Point2d(test_point.x + ux[0], test_point.y + ux[1]),
                                    model,
                                    plane);
      Eigen::Vector2f uy(uy_end.x - test_point.x, uy_end.y - test_point.y);

      Eigen::Matrix2f A;
      A << ux[0], uy[0],
        ux[1], uy[1];
      bool excluded = false;
      double max_alpha = -DBL_MAX;
      double max_beta = -DBL_MAX;
      for (size_t i = 0; i < indices.size(); i++) {
        Eigen::Vector2f p_q = Eigen::Vector2f(indices[i].x, indices[i].y) - Eigen::Vector2f(test_point.x, test_point.y);
        Eigen::Vector2f a_b = A.inverse() * p_q;
        double alpha = a_b[0];
        double beta = a_b[1];
        if (alpha < 0 || beta < 0) {
          excluded = true;
          break;
        }
        if (alpha > max_alpha) {
          max_alpha = alpha;
        }
        if (beta > max_beta) {
          max_beta = beta;
        }
        
      }
      if (!excluded) {
        angles.push_back(angle);
        max_x.push_back(max_alpha);
        max_y.push_back(max_beta);
      }
    }
  }