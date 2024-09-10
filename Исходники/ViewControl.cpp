bool ViewControl::ConvertToPinholeCameraParameters(
        PinholeCameraIntrinsic &intrinsic, Eigen::Matrix4d &extrinsic)
{
    if (window_height_ <= 0 || window_width_ <= 0) {
        PrintWarning("[ViewControl] ConvertToPinholeCameraParameters() failed because window height and width are not set.\n");
        return false;
    }
    if (GetProjectionType() == ProjectionType::Orthogonal) {
        PrintWarning("[ViewControl] ConvertToPinholeCameraParameters() failed because orthogonal view cannot be translated to a pinhole camera.\n");
        return false;
    }
    SetProjectionParameters();
    intrinsic.width_ = window_width_;
    intrinsic.height_ = window_height_;
    intrinsic.intrinsic_matrix_.setIdentity();
    double fov_rad = field_of_view_ / 180.0 * M_PI;
    double tan_half_fov = std::tan(fov_rad / 2.0);
    intrinsic.intrinsic_matrix_(0, 0) = intrinsic.intrinsic_matrix_(1, 1) =
            (double)window_height_ / tan_half_fov / 2.0;
    intrinsic.intrinsic_matrix_(0, 2) = (double)window_width_ / 2.0 - 0.5;
    intrinsic.intrinsic_matrix_(1, 2) = (double)window_height_ / 2.0 - 0.5;
    extrinsic.setZero();
    Eigen::Vector3d front_dir = front_.normalized();
    Eigen::Vector3d up_dir = up_.normalized();
    Eigen::Vector3d right_dir = right_.normalized();
    extrinsic.block<1, 3>(0, 0) = right_dir.transpose();
    extrinsic.block<1, 3>(1, 0) = -up_dir.transpose();
    extrinsic.block<1, 3>(2, 0) = -front_dir.transpose();
    extrinsic(0, 3) = -right_dir.dot(eye_);
    extrinsic(1, 3) = up_dir.dot(eye_);
    extrinsic(2, 3) = front_dir.dot(eye_);
    extrinsic(3, 3) = 1.0;
    return true;
}