static Eigen::Vector3f
quaternion_derivative_to_angular_velocity(
    const Eigen::Quaternionf &current_orientation,
    const Eigen::Quaternionf &quaternion_derivative)
{
    Eigen::Quaternionf inv_orientation = current_orientation.conjugate();
    auto q_ang_vel = (quaternion_derivative*inv_orientation).coeffs() * 2.f;
    Eigen::Vector3f ang_vel(q_ang_vel.x(), q_ang_vel.y(), q_ang_vel.z());

    return ang_vel;
}