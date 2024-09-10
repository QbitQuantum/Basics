template <typename PointInT, typename PointOutT> void
pcl::IntegralImageNormalEstimation<PointInT, PointOutT>::computePointNormal (
    const int pos_x, const int pos_y, const unsigned point_index, PointOutT &normal)
{
  float bad_point = std::numeric_limits<float>::quiet_NaN ();

  if (normal_estimation_method_ == COVARIANCE_MATRIX)
  {
    if (!init_covariance_matrix_)
      initCovarianceMatrixMethod ();

    unsigned count = integral_image_XYZ_.getFiniteElementsCount (pos_x - (rect_width_2_), pos_y - (rect_height_2_), rect_width_, rect_height_);

    // no valid points within the rectangular reagion?
    if (count == 0)
    {
      normal.normal_x = normal.normal_y = normal.normal_z = normal.curvature = std::numeric_limits<float>::quiet_NaN ();
      return;
    }

    EIGEN_ALIGN16 Eigen::Matrix3f covariance_matrix;
    Eigen::Vector3f center;
    typename IntegralImage2D<float, 3>::SecondOrderType so_elements;
    center = integral_image_XYZ_.getFirstOrderSum(pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_).cast<float> ();
    so_elements = integral_image_XYZ_.getSecondOrderSum(pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);

    covariance_matrix.coeffRef (0) = static_cast<float> (so_elements [0]);
    covariance_matrix.coeffRef (1) = covariance_matrix.coeffRef (3) = static_cast<float> (so_elements [1]);
    covariance_matrix.coeffRef (2) = covariance_matrix.coeffRef (6) = static_cast<float> (so_elements [2]);
    covariance_matrix.coeffRef (4) = static_cast<float> (so_elements [3]);
    covariance_matrix.coeffRef (5) = covariance_matrix.coeffRef (7) = static_cast<float> (so_elements [4]);
    covariance_matrix.coeffRef (8) = static_cast<float> (so_elements [5]);
    covariance_matrix -= (center * center.transpose ()) / static_cast<float> (count);
    float eigen_value;
    Eigen::Vector3f eigen_vector;
    pcl::eigen33 (covariance_matrix, eigen_value, eigen_vector);
    //pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, eigen_vector);
    pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, eigen_vector[0], eigen_vector[1], eigen_vector[2]);
    normal.getNormalVector3fMap () = eigen_vector;

    // Compute the curvature surface change
    if (eigen_value > 0.0)
      normal.curvature = fabsf (eigen_value / (covariance_matrix.coeff (0) + covariance_matrix.coeff (4) + covariance_matrix.coeff (8)));
    else
      normal.curvature = 0;

    return;
  }
  else if (normal_estimation_method_ == AVERAGE_3D_GRADIENT)
  {
    if (!init_average_3d_gradient_)
      initAverage3DGradientMethod ();

    unsigned count_x = integral_image_DX_.getFiniteElementsCount (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);
    unsigned count_y = integral_image_DY_.getFiniteElementsCount (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);
    if (count_x == 0 || count_y == 0)
    {
      normal.normal_x = normal.normal_y = normal.normal_z = normal.curvature = std::numeric_limits<float>::quiet_NaN ();
      return;
    }
    Eigen::Vector3d gradient_x = integral_image_DX_.getFirstOrderSum (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);
    Eigen::Vector3d gradient_y = integral_image_DY_.getFirstOrderSum (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);

    Eigen::Vector3d normal_vector = gradient_y.cross (gradient_x);
    double normal_length = normal_vector.squaredNorm ();
    if (normal_length == 0.0f)
    {
      normal.getNormalVector4fMap ().setConstant (bad_point);
      normal.curvature = bad_point;
      return;
    }

    normal_vector /= sqrt (normal_length);

    float nx = static_cast<float> (normal_vector [0]);
    float ny = static_cast<float> (normal_vector [1]);
    float nz = static_cast<float> (normal_vector [2]);

    //pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, normal_vector);
    pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, nx, ny, nz);

    normal.normal_x = nx;
    normal.normal_y = ny;
    normal.normal_z = nz;
    normal.curvature = bad_point;
    return;
  }
  else if (normal_estimation_method_ == AVERAGE_DEPTH_CHANGE)
  {
    if (!init_depth_change_)
      initAverageDepthChangeMethod ();

//    unsigned count = integral_image_depth_.getFiniteElementsCount (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, rect_height_);
//    if (count == 0)
//    {
//      normal.normal_x = normal.normal_y = normal.normal_z = normal.curvature = std::numeric_limits<float>::quiet_NaN ();
//      return;
//    }
//    const float mean_L_z = integral_image_depth_.getFirstOrderSum (pos_x - rect_width_2_ - 1, pos_y - rect_height_2_    , rect_width_ - 1, rect_height_ - 1) / ((rect_width_-1)*(rect_height_-1));
//    const float mean_R_z = integral_image_depth_.getFirstOrderSum (pos_x - rect_width_2_ + 1, pos_y - rect_height_2_    , rect_width_ - 1, rect_height_ - 1) / ((rect_width_-1)*(rect_height_-1));
//    const float mean_U_z = integral_image_depth_.getFirstOrderSum (pos_x - rect_width_2_    , pos_y - rect_height_2_ - 1, rect_width_ - 1, rect_height_ - 1) / ((rect_width_-1)*(rect_height_-1));
//    const float mean_D_z = integral_image_depth_.getFirstOrderSum (pos_x - rect_width_2_    , pos_y - rect_height_2_ + 1, rect_width_ - 1, rect_height_ - 1) / ((rect_width_-1)*(rect_height_-1));

    // width and height are at least 3 x 3
    unsigned count_L_z = integral_image_depth_.getFiniteElementsCount (pos_x - rect_width_2_, pos_y - rect_height_4_, rect_width_2_, rect_height_2_);
    unsigned count_R_z = integral_image_depth_.getFiniteElementsCount (pos_x + 1            , pos_y - rect_height_4_, rect_width_2_, rect_height_2_);
    unsigned count_U_z = integral_image_depth_.getFiniteElementsCount (pos_x - rect_width_4_, pos_y - rect_height_2_, rect_width_2_, rect_height_2_);
    unsigned count_D_z = integral_image_depth_.getFiniteElementsCount (pos_x - rect_width_4_, pos_y + 1             , rect_width_2_, rect_height_2_);

    if (count_L_z == 0 || count_R_z == 0 || count_U_z == 0 || count_D_z == 0)
    {
      normal.normal_x = normal.normal_y = normal.normal_z = normal.curvature = std::numeric_limits<float>::quiet_NaN ();
      return;
    }

    float mean_L_z = static_cast<float> (integral_image_depth_.getFirstOrderSum (pos_x - rect_width_2_, pos_y - rect_height_4_, rect_width_2_, rect_height_2_) / count_L_z);
    float mean_R_z = static_cast<float> (integral_image_depth_.getFirstOrderSum (pos_x + 1            , pos_y - rect_height_4_, rect_width_2_, rect_height_2_) / count_R_z);
    float mean_U_z = static_cast<float> (integral_image_depth_.getFirstOrderSum (pos_x - rect_width_4_, pos_y - rect_height_2_, rect_width_2_, rect_height_2_) / count_U_z);
    float mean_D_z = static_cast<float> (integral_image_depth_.getFirstOrderSum (pos_x - rect_width_4_, pos_y + 1             , rect_width_2_, rect_height_2_) / count_D_z);

    PointInT pointL = input_->points[point_index - rect_width_4_ - 1];
    PointInT pointR = input_->points[point_index + rect_width_4_ + 1];
    PointInT pointU = input_->points[point_index - rect_height_4_ * input_->width - 1];
    PointInT pointD = input_->points[point_index + rect_height_4_ * input_->width + 1];

    const float mean_x_z = mean_R_z - mean_L_z;
    const float mean_y_z = mean_D_z - mean_U_z;

    const float mean_x_x = pointR.x - pointL.x;
    const float mean_x_y = pointR.y - pointL.y;
    const float mean_y_x = pointD.x - pointU.x;
    const float mean_y_y = pointD.y - pointU.y;

    float normal_x = mean_x_y * mean_y_z - mean_x_z * mean_y_y;
    float normal_y = mean_x_z * mean_y_x - mean_x_x * mean_y_z;
    float normal_z = mean_x_x * mean_y_y - mean_x_y * mean_y_x;

    const float normal_length = (normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);

    if (normal_length == 0.0f)
    {
      normal.getNormalVector4fMap ().setConstant (bad_point);
      normal.curvature = bad_point;
      return;
    }

    pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, normal_x, normal_y, normal_z);
    
    const float scale = 1.0f / sqrt (normal_length);

    normal.normal_x = normal_x * scale;
    normal.normal_y = normal_y * scale;
    normal.normal_z = normal_z * scale;
    normal.curvature = bad_point;

    return;
  }
  else if (normal_estimation_method_ == SIMPLE_3D_GRADIENT)
  {
    if (!init_simple_3d_gradient_)
      initSimple3DGradientMethod ();

    // this method does not work if lots of NaNs are in the neighborhood of the point
    Eigen::Vector3d gradient_x = integral_image_XYZ_.getFirstOrderSum (pos_x + rect_width_2_, pos_y - rect_height_2_, 1, rect_height_) -
                                 integral_image_XYZ_.getFirstOrderSum (pos_x - rect_width_2_, pos_y - rect_height_2_, 1, rect_height_);

    Eigen::Vector3d gradient_y = integral_image_XYZ_.getFirstOrderSum (pos_x - rect_width_2_, pos_y + rect_height_2_, rect_width_, 1) -
                                 integral_image_XYZ_.getFirstOrderSum (pos_x - rect_width_2_, pos_y - rect_height_2_, rect_width_, 1);
    Eigen::Vector3d normal_vector = gradient_y.cross (gradient_x);
    double normal_length = normal_vector.squaredNorm ();
    if (normal_length == 0.0f)
    {
      normal.getNormalVector4fMap ().setConstant (bad_point);
      normal.curvature = bad_point;
      return;
    }

    normal_vector /= sqrt (normal_length);

    float nx = static_cast<float> (normal_vector [0]);
    float ny = static_cast<float> (normal_vector [1]);
    float nz = static_cast<float> (normal_vector [2]);

    //pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, normal_vector);
    pcl::flipNormalTowardsViewpoint (input_->points[point_index], vpx_, vpy_, vpz_, nx, ny, nz);
    
    normal.normal_x = nx;
    normal.normal_y = ny;
    normal.normal_z = nz;
    normal.curvature = bad_point;
    return;
  }

  normal.getNormalVector4fMap ().setConstant (bad_point);
  normal.curvature = bad_point;
  return;
}