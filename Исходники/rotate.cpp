void QuaternionRotate::set(double angle, Point u) {
    this->angle = angle;
    u.normalize();
    first = Eigen::AngleAxisd(angle, u);
    second << 0, -u.z(), u.y(), u.z(), 0, -u.x(), -u.y(), u.x(), 0;
    second = Eigen::Matrix3d::Identity() + second * std::sin(angle) + second * second * (1 - std::cos(angle));

    // Quaternion can be converted to rotation matrix:
    // second = first.toRotationMatrix()
}