gtsam::Pose3 Convert(const Eigen::Isometry3f& iso)
{
    gtsam::Matrix3 mat = iso.linear().cast<double>();
    Eigen::Vector3d trans = iso.translation().cast<double>();
    return gtsam::Pose3(mat, gtsam::Point3(trans));
}