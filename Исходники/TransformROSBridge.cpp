void TransformROSBridge::calculateTwist(const tf::Transform& _current_trans, const tf::Transform& _prev_trans, tf::Vector3& _linear_twist, tf::Vector3& _angular_twist, double _dt)
{
    // current rotation matrix
    tf::Matrix3x3 current_basis = _current_trans.getBasis();

    // linear twist
    tf::Vector3 current_origin = _current_trans.getOrigin();
    tf::Vector3 prev_origin = _prev_trans.getOrigin();
    _linear_twist = current_basis.transpose() * ((current_origin - prev_origin) / _dt);

    // angular twist
    // R = exp(omega_w*dt) * prev_R
    // omega_w is described in global coordinates in relationships of twist transformation.
    // it is easier to calculate omega using hrp functions than tf functions
    tf::Matrix3x3 prev_basis = _prev_trans.getBasis();
    double current_rpy[3], prev_rpy[3];
    current_basis.getRPY(current_rpy[0], current_rpy[1], current_rpy[2]);
    prev_basis.getRPY(prev_rpy[0], prev_rpy[1], prev_rpy[2]);
    hrp::Matrix33 current_hrpR = hrp::rotFromRpy(current_rpy[0], current_rpy[1], current_rpy[2]);
    hrp::Matrix33 prev_hrpR = hrp::rotFromRpy(prev_rpy[0], prev_rpy[1], prev_rpy[2]);
    hrp::Vector3 hrp_omega = current_hrpR.transpose() * hrp::omegaFromRot(current_hrpR * prev_hrpR.transpose()) / _dt;
    _angular_twist.setX(hrp_omega[0]);
    _angular_twist.setY(hrp_omega[1]);
    _angular_twist.setZ(hrp_omega[2]);

    return;
}