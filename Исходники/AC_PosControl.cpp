/// accel_to_lean_angles - horizontal desired acceleration to lean angles
///    converts desired accelerations provided in lat/lon frame to roll/pitch angles
void AC_PosControl::accel_to_lean_angles(float dt, float ekfNavVelGainScaler)
{
    float accel_right, accel_forward;
    float lean_angle_max = _attitude_control.lean_angle_max();

    // reset accel to current desired acceleration
    if (_flags.reset_accel_to_lean_xy) {
        _accel_target_jerk_limited.x = _accel_target.x;
        _accel_target_jerk_limited.y = _accel_target.y;
        _accel_target_filter.reset(Vector2f(_accel_target.x, _accel_target.y));
        _flags.reset_accel_to_lean_xy = false;
    }

    // apply jerk limit of 17 m/s^3 - equates to a worst case of about 100 deg/sec/sec
    float max_delta_accel = dt * POSCONTROL_JERK_LIMIT_CMSSS;

    Vector2f accel_in(_accel_target.x, _accel_target.y);
    Vector2f accel_change = accel_in-_accel_target_jerk_limited;
    float accel_change_length = accel_change.length();

    if(accel_change_length > max_delta_accel) {
        accel_change *= max_delta_accel/accel_change_length;
    }
    _accel_target_jerk_limited += accel_change;

    // lowpass filter on NE accel
    _accel_target_filter.set_cutoff_frequency(min(_accel_xy_filt_hz, 5.0f*ekfNavVelGainScaler));
    Vector2f accel_target_filtered = _accel_target_filter.apply(_accel_target_jerk_limited, dt);

    // rotate accelerations into body forward-right frame
    accel_forward = accel_target_filtered.x*_ahrs.cos_yaw() + accel_target_filtered.y*_ahrs.sin_yaw();
    accel_right = -accel_target_filtered.x*_ahrs.sin_yaw() + accel_target_filtered.y*_ahrs.cos_yaw();

    // update angle targets that will be passed to stabilize controller
    _pitch_target = constrain_float(atanf(-accel_forward/(GRAVITY_MSS * 100))*(18000/M_PI_F),-lean_angle_max, lean_angle_max);
    float cos_pitch_target = cosf(_pitch_target*M_PI_F/18000);
    _roll_target = constrain_float(atanf(accel_right*cos_pitch_target/(GRAVITY_MSS * 100))*(18000/M_PI_F), -lean_angle_max, lean_angle_max);
}