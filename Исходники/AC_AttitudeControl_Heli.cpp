// rate_bf_to_motor_roll_pitch - ask the rate controller to calculate the motor outputs to achieve the target rate in radians/second
void AC_AttitudeControl_Heli::rate_bf_to_motor_roll_pitch(const Vector3f &rate_rads, float rate_roll_target_rads, float rate_pitch_target_rads)
{
    float roll_pd, roll_i, roll_ff;             // used to capture pid values
    float pitch_pd, pitch_i, pitch_ff;          // used to capture pid values
    float rate_roll_error_rads, rate_pitch_error_rads;    // simply target_rate - current_rate
    float roll_out, pitch_out;

    // calculate error
    rate_roll_error_rads = rate_roll_target_rads - rate_rads.x;
    rate_pitch_error_rads = rate_pitch_target_rads - rate_rads.y;

    // pass error to PID controller
    _pid_rate_roll.set_input_filter_all(rate_roll_error_rads);
    _pid_rate_roll.set_desired_rate(rate_roll_target_rads);
    _pid_rate_pitch.set_input_filter_all(rate_pitch_error_rads);
    _pid_rate_pitch.set_desired_rate(rate_pitch_target_rads);

    // call p and d controllers
    roll_pd = _pid_rate_roll.get_p() + _pid_rate_roll.get_d();
    pitch_pd = _pid_rate_pitch.get_p() + _pid_rate_pitch.get_d();

    // get roll i term
    roll_i = _pid_rate_roll.get_integrator();

    // update i term as long as we haven't breached the limits or the I term will certainly reduce
    if (!_flags_heli.limit_roll || ((roll_i>0&&rate_roll_error_rads<0)||(roll_i<0&&rate_roll_error_rads>0))){
		if (_flags_heli.leaky_i){
			roll_i = _pid_rate_roll.get_leaky_i(AC_ATTITUDE_HELI_RATE_INTEGRATOR_LEAK_RATE);
		}else{
			roll_i = _pid_rate_roll.get_i();
		}
    }

    // get pitch i term
    pitch_i = _pid_rate_pitch.get_integrator();

    // update i term as long as we haven't breached the limits or the I term will certainly reduce
    if (!_flags_heli.limit_pitch || ((pitch_i>0&&rate_pitch_error_rads<0)||(pitch_i<0&&rate_pitch_error_rads>0))){
		if (_flags_heli.leaky_i) {
			pitch_i = _pid_rate_pitch.get_leaky_i(AC_ATTITUDE_HELI_RATE_INTEGRATOR_LEAK_RATE);
		}else{
			pitch_i = _pid_rate_pitch.get_i();
		}
    }
    
    // For legacy reasons, we convert to centi-degrees before inputting to the feedforward
    roll_ff = roll_feedforward_filter.apply(_pid_rate_roll.get_ff(rate_roll_target_rads), _dt);
    pitch_ff = pitch_feedforward_filter.apply(_pid_rate_pitch.get_ff(rate_pitch_target_rads), _dt);

    // add feed forward and final output
    roll_out = roll_pd + roll_i + roll_ff;
    pitch_out = pitch_pd + pitch_i + pitch_ff;

    // constrain output and update limit flags
    if (fabsf(roll_out) > AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX) {
        roll_out = constrain_float(roll_out,-AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX,AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX);
        _flags_heli.limit_roll = true;
    }else{
        _flags_heli.limit_roll = false;
    }
    if (fabsf(pitch_out) > AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX) {
        pitch_out = constrain_float(pitch_out,-AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX,AC_ATTITUDE_RATE_RP_CONTROLLER_OUT_MAX);
        _flags_heli.limit_pitch = true;
    }else{
        _flags_heli.limit_pitch = false;
    }

    // output to motors
    _motors.set_roll(roll_out);
    _motors.set_pitch(pitch_out);

    // Piro-Comp, or Pirouette Compensation is a pre-compensation calculation, which basically rotates the Roll and Pitch Rate I-terms as the
    // helicopter rotates in yaw.  Much of the built-up I-term is needed to tip the disk into the incoming wind.  Fast yawing can create an instability
    // as the built-up I-term in one axis must be reduced, while the other increases.  This helps solve that by rotating the I-terms before the error occurs.
    // It does assume that the rotor aerodynamics and mechanics are essentially symmetrical about the main shaft, which is a generally valid assumption. 
    if (_piro_comp_enabled){

        int32_t         piro_roll_i, piro_pitch_i;            // used to hold I-terms while doing piro comp

        piro_roll_i  = roll_i;
        piro_pitch_i = pitch_i;

        Vector2f yawratevector;
        yawratevector.x     = cosf(-rate_rads.z * _dt);
        yawratevector.y     = sinf(-rate_rads.z * _dt);
        yawratevector.normalize();

        roll_i      = piro_roll_i * yawratevector.x - piro_pitch_i * yawratevector.y;
        pitch_i     = piro_pitch_i * yawratevector.x + piro_roll_i * yawratevector.y;

        _pid_rate_pitch.set_integrator(pitch_i);
        _pid_rate_roll.set_integrator(roll_i);
    }

}