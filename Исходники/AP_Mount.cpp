/// Stabilizes mount relative to the Earth's frame
/// Inputs:
///    _roll_control_angle   desired roll       angle in radians,
///    _tilt_control_angle   desired tilt/pitch angle in radians,
///    _pan_control_angle    desired pan/yaw    angle in radians
/// Outputs:
///    _roll_angle           stabilized roll       angle in degrees,
///    _tilt_angle           stabilized tilt/pitch angle in degrees,
///    _pan_angle            stabilized pan/yaw    angle in degrees
void
AP_Mount::stabilize()
{
#if MNT_STABILIZE_OPTION == ENABLED
    // only do the full 3D frame transform if we are doing pan control
    if (_stab_pan) {
        Matrix3f m;                         ///< holds 3 x 3 matrix, var is used as temp in calcs
        Matrix3f cam;                       ///< Rotation matrix earth to camera. Desired camera from input.
        Matrix3f gimbal_target;             ///< Rotation matrix from plane to camera. Then Euler angles to the servos.
        m = _ahrs.get_dcm_matrix();
        m.transpose();
        cam.from_euler(_roll_control_angle, _tilt_control_angle, _pan_control_angle);
        gimbal_target = m * cam;
        gimbal_target.to_euler(&_roll_angle, &_tilt_angle, &_pan_angle);
        _roll_angle  = _stab_roll ? degrees(_roll_angle) : degrees(_roll_control_angle);
        _tilt_angle  = _stab_tilt ? degrees(_tilt_angle) : degrees(_tilt_control_angle);
        _pan_angle   = degrees(_pan_angle);
    } else {
        // otherwise base mount roll and tilt on the ahrs
        // roll/tilt attitude, plus any requested angle
        _roll_angle  = degrees(_roll_control_angle);
        _tilt_angle  = degrees(_tilt_control_angle);
        _pan_angle   = degrees(_pan_control_angle);
        if (_stab_roll) {
            _roll_angle -= degrees(_ahrs.roll);
        }
        if (_stab_tilt) {
            _tilt_angle -= degrees(_ahrs.pitch);
        }

        // Add lead filter.
        const Vector3f &gyro = _ahrs.get_gyro();

        if (_stab_roll && _roll_stb_lead != 0.0f && fabsf(_ahrs.pitch) < M_PI/3.0f) {
            // Compute rate of change of euler roll angle
            float roll_rate = gyro.x + (_ahrs.sin_pitch() / _ahrs.cos_pitch()) * (gyro.y * _ahrs.sin_roll() + gyro.z * _ahrs.cos_roll());
            _roll_angle -= degrees(roll_rate) * _roll_stb_lead;
        }

        if (_stab_tilt && _pitch_stb_lead != 0.0f) {
            // Compute rate of change of euler pitch angle
            float pitch_rate = _ahrs.cos_pitch() * gyro.y - _ahrs.sin_roll() * gyro.z;
            _tilt_angle -= degrees(pitch_rate) * _pitch_stb_lead;
        }
    }
#endif
}