// stabilize - stabilizes the mount relative to the Earth's frame
//  input: _angle_ef_target_rad (earth frame targets in radians)
//  output: _angle_bf_output_deg (body frame angles in degrees)
void AP_Mount_Servo::stabilize()
{
    AP_AHRS &ahrs = AP::ahrs();
    // only do the full 3D frame transform if we are doing pan control
    if (_state._stab_pan) {
        Matrix3f m;                         ///< holds 3 x 3 matrix, var is used as temp in calcs
        Matrix3f cam;                       ///< Rotation matrix earth to camera. Desired camera from input.
        Matrix3f gimbal_target;             ///< Rotation matrix from plane to camera. Then Euler angles to the servos.
        m = ahrs.get_rotation_body_to_ned();
        m.transpose();
        cam.from_euler(_angle_ef_target_rad.x, _angle_ef_target_rad.y, _angle_ef_target_rad.z);
        gimbal_target = m * cam;
        gimbal_target.to_euler(&_angle_bf_output_deg.x, &_angle_bf_output_deg.y, &_angle_bf_output_deg.z);
        _angle_bf_output_deg.x  = _state._stab_roll ? degrees(_angle_bf_output_deg.x) : degrees(_angle_ef_target_rad.x);
        _angle_bf_output_deg.y  = _state._stab_tilt ? degrees(_angle_bf_output_deg.y) : degrees(_angle_ef_target_rad.y);
        _angle_bf_output_deg.z = degrees(_angle_bf_output_deg.z);
    } else {
        // otherwise base mount roll and tilt on the ahrs
        // roll/tilt attitude, plus any requested angle
        _angle_bf_output_deg.x = degrees(_angle_ef_target_rad.x);
        _angle_bf_output_deg.y = degrees(_angle_ef_target_rad.y);
        _angle_bf_output_deg.z = degrees(_angle_ef_target_rad.z);
        if (_state._stab_roll) {
            _angle_bf_output_deg.x -= degrees(ahrs.roll);
        }
        if (_state._stab_tilt) {
            _angle_bf_output_deg.y -= degrees(ahrs.pitch);
        }

        // lead filter
        const Vector3f &gyro = ahrs.get_gyro();

        if (_state._stab_roll && !is_zero(_state._roll_stb_lead) && fabsf(ahrs.pitch) < M_PI/3.0f) {
            // Compute rate of change of euler roll angle
            float roll_rate = gyro.x + (ahrs.sin_pitch() / ahrs.cos_pitch()) * (gyro.y * ahrs.sin_roll() + gyro.z * ahrs.cos_roll());
            _angle_bf_output_deg.x -= degrees(roll_rate) * _state._roll_stb_lead;
        }

        if (_state._stab_tilt && !is_zero(_state._pitch_stb_lead)) {
            // Compute rate of change of euler pitch angle
            float pitch_rate = ahrs.cos_pitch() * gyro.y - ahrs.sin_roll() * gyro.z;
            _angle_bf_output_deg.y -= degrees(pitch_rate) * _state._pitch_stb_lead;
        }
    }
}