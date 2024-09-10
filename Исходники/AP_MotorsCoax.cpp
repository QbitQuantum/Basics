// sends commands to the motors
void AP_MotorsCoax::output_armed_stabilizing()
{
    float   roll_thrust;                // roll thrust input value, +/- 1.0
    float   pitch_thrust;               // pitch thrust input value, +/- 1.0
    float   yaw_thrust;                 // yaw thrust input value, +/- 1.0
    float   throttle_thrust;            // throttle thrust input value, 0.0 - 1.0
    float   thrust_min_rpy;             // the minimum throttle setting that will not limit the roll and pitch output
    float   thr_adj;                    // the difference between the pilot's desired throttle and throttle_thrust_best_rpy
    float   thrust_out;                 //
    float   rp_scale = 1.0f;           // this is used to scale the roll, pitch and yaw to fit within the motor limits
    float   actuator_allowed = 0.0f;    // amount of yaw we can fit in

    // apply voltage and air pressure compensation
    roll_thrust = _roll_in * get_compensation_gain();
    pitch_thrust = _pitch_in * get_compensation_gain();
    yaw_thrust = _yaw_in * get_compensation_gain();
    throttle_thrust = get_throttle() * get_compensation_gain();

    // sanity check throttle is above zero and below current limited throttle
    if (throttle_thrust <= 0.0f) {
        throttle_thrust = 0.0f;
        limit.throttle_lower = true;
    }
    if (throttle_thrust >= _throttle_thrust_max) {
        throttle_thrust = _throttle_thrust_max;
        limit.throttle_upper = true;
    }

    _throttle_avg_max = constrain_float(_throttle_avg_max, throttle_thrust, _throttle_thrust_max);

    float rp_thrust_max = MAX(fabsf(roll_thrust), fabsf(pitch_thrust));

    // calculate how much roll and pitch must be scaled to leave enough range for the minimum yaw
    if (is_zero(rp_thrust_max)) {
        rp_scale = 1.0f;
    } else {
        rp_scale = constrain_float((1.0f - MIN(fabsf(yaw_thrust), 0.5f*(float)_yaw_headroom/1000.0f)) / rp_thrust_max, 0.0f, 1.0f);
        if (rp_scale < 1.0f) {
            limit.roll_pitch = true;
        }
    }

    actuator_allowed = 2.0f * (1.0f - rp_scale * rp_thrust_max);
    if (fabsf(yaw_thrust) > actuator_allowed) {
        yaw_thrust = constrain_float(yaw_thrust, -actuator_allowed, actuator_allowed);
        limit.yaw = true;
    }

    // calculate the minimum thrust that doesn't limit the roll, pitch and yaw forces
    thrust_min_rpy = MAX(fabsf(rp_scale * rp_thrust_max), fabsf(yaw_thrust));

    thr_adj = throttle_thrust - _throttle_avg_max;
    if (thr_adj < (thrust_min_rpy - _throttle_avg_max)) {
        // Throttle can't be reduced to the desired level because this would mean roll or pitch control
        // would not be able to reach the desired level because of lack of thrust.
        thr_adj = MIN(thrust_min_rpy, _throttle_avg_max) - _throttle_avg_max;
    }

    // calculate the throttle setting for the lift fan
    thrust_out = _throttle_avg_max + thr_adj;

    if (fabsf(yaw_thrust) > thrust_out) {
        yaw_thrust = constrain_float(yaw_thrust, -thrust_out, thrust_out);
        limit.yaw = true;
    }

    _thrust_yt_ccw = thrust_out + 0.5f * yaw_thrust;
    _thrust_yt_cw = thrust_out - 0.5f * yaw_thrust;

    // limit thrust out for calculation of actuator gains
    float thrust_out_actuator = constrain_float(MAX(_throttle_hover*0.5f,thrust_out), 0.1f, 1.0f);

    if (is_zero(thrust_out)) {
        limit.roll_pitch = true;
    }
    // force of a lifting surface is approximately equal to the angle of attack times the airflow velocity squared
    // static thrust is proportional to the airflow velocity squared
    // therefore the torque of the roll and pitch actuators should be approximately proportional to
    // the angle of attack multiplied by the static thrust.
    _actuator_out[0] = roll_thrust/thrust_out_actuator;
    _actuator_out[1] = pitch_thrust/thrust_out_actuator;
    if (fabsf(_actuator_out[0]) > 1.0f) {
        limit.roll_pitch = true;
        _actuator_out[0] = constrain_float(_actuator_out[0], -1.0f, 1.0f);
    }
    if (fabsf(_actuator_out[1]) > 1.0f) {
        limit.roll_pitch = true;
        _actuator_out[1] = constrain_float(_actuator_out[1], -1.0f, 1.0f);
    }
    _actuator_out[2] = -_actuator_out[0];
    _actuator_out[3] = -_actuator_out[1];
}