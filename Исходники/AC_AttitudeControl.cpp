// thrust_heading_rotation_angles - calculates two ordered rotations to move the att_from_quat quaternion to the att_to_quat quaternion.
// The first rotation corrects the thrust vector and the second rotation corrects the heading vector.
void AC_AttitudeControl::thrust_heading_rotation_angles(Quaternion& att_to_quat, const Quaternion& att_from_quat, Vector3f& att_diff_angle, float& thrust_vec_dot)
{
    Matrix3f att_to_rot_matrix; // rotation from the target body frame to the inertial frame.
    att_to_quat.rotation_matrix(att_to_rot_matrix);
    Vector3f att_to_thrust_vec = att_to_rot_matrix*Vector3f(0.0f,0.0f,1.0f);

    Matrix3f att_from_rot_matrix; // rotation from the current body frame to the inertial frame.
    att_from_quat.rotation_matrix(att_from_rot_matrix);
    Vector3f att_from_thrust_vec = att_from_rot_matrix*Vector3f(0.0f,0.0f,1.0f);

    // the cross product of the desired and target thrust vector defines the rotation vector
    Vector3f thrust_vec_cross = att_from_thrust_vec % att_to_thrust_vec;

    // the dot product is used to calculate the angle between the target and desired thrust vectors
    thrust_vec_dot = acosf(constrain_float(att_from_thrust_vec * att_to_thrust_vec,-1.0f,1.0f));

    // Normalize the thrust rotation vector
    float thrust_vector_length = thrust_vec_cross.length();
    if(is_zero(thrust_vector_length) || is_zero(thrust_vec_dot)){
        thrust_vec_cross = Vector3f(0,0,1);
        thrust_vec_dot = 0.0f;
    }else{
        thrust_vec_cross /= thrust_vector_length;
    }
    Quaternion thrust_vec_correction_quat;
    thrust_vec_correction_quat.from_axis_angle(thrust_vec_cross, thrust_vec_dot);
    thrust_vec_correction_quat = att_from_quat.inverse()*thrust_vec_correction_quat*att_from_quat;

    // calculate the remaining rotation required after thrust vector is rotated
    Quaternion heading_quat = thrust_vec_correction_quat.inverse()*att_from_quat.inverse()*att_to_quat;

    Vector3f rotation;
    thrust_vec_correction_quat.to_axis_angle(rotation);
    att_diff_angle.x = rotation.x;
    att_diff_angle.y = rotation.y;

    heading_quat.to_axis_angle(rotation);
    att_diff_angle.z = rotation.z;
    if(!is_zero(_p_angle_yaw.kP()) && fabsf(att_diff_angle.z) > AC_ATTITUDE_ACCEL_Y_CONTROLLER_MAX_RADSS/_p_angle_yaw.kP()){
        att_diff_angle.z = constrain_float(wrap_PI(att_diff_angle.z), -AC_ATTITUDE_ACCEL_Y_CONTROLLER_MAX_RADSS/_p_angle_yaw.kP(), AC_ATTITUDE_ACCEL_Y_CONTROLLER_MAX_RADSS/_p_angle_yaw.kP());
        heading_quat.from_axis_angle(Vector3f(0.0f,0.0f,att_diff_angle.z));
        att_to_quat = att_from_quat*thrust_vec_correction_quat*heading_quat;
    }
}