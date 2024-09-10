float ECL_PitchController::control_bodyrate(const ECL_ControlData &ctl_data)
{
	/* Do not calculate control signal with bad inputs */
	if (!(PX4_ISFINITE(ctl_data.roll) &&
	      PX4_ISFINITE(ctl_data.pitch) &&
	      PX4_ISFINITE(ctl_data.pitch_rate) &&
	      PX4_ISFINITE(ctl_data.yaw_rate) &&
	      PX4_ISFINITE(ctl_data.yaw_rate_setpoint) &&
	      PX4_ISFINITE(ctl_data.airspeed_min) &&
	      PX4_ISFINITE(ctl_data.airspeed_max) &&
	      PX4_ISFINITE(ctl_data.scaler))) {
		perf_count(_nonfinite_input_perf);
		return math::constrain(_last_output, -1.0f, 1.0f);
	}

	/* get the usual dt estimate */
	uint64_t dt_micros = ecl_elapsed_time(&_last_run);
	_last_run = ecl_absolute_time();
	float dt = (float)dt_micros * 1e-6f;

	/* lock integral for long intervals */
	bool lock_integrator = ctl_data.lock_integrator;

	if (dt_micros > 500000) {
		lock_integrator = true;
	}

	/* Transform setpoint to body angular rates (jacobian) */
	_bodyrate_setpoint = cosf(ctl_data.roll) * _rate_setpoint +
			     cosf(ctl_data.pitch) * sinf(ctl_data.roll) * ctl_data.yaw_rate_setpoint;

	/* apply turning offset to desired bodyrate setpoint*/
	/* flying inverted (wings upside down)*/
	bool inverted = false;
	float constrained_roll;
	/* roll is used as feedforward term and inverted flight needs to be considered */
	if (fabsf(ctl_data.roll) < math::radians(90.0f)) {
		/* not inverted, but numerically still potentially close to infinity */
		constrained_roll = math::constrain(ctl_data.roll, math::radians(-80.0f), math::radians(80.0f));

	} else {
		/* inverted flight, constrain on the two extremes of -pi..+pi to avoid infinity */
		inverted = true;
		/* note: the ranges are extended by 10 deg here to avoid numeric resolution effects */
		if (ctl_data.roll > 0.0f) {
			/* right hemisphere */
			constrained_roll = math::constrain(ctl_data.roll, math::radians(100.0f), math::radians(180.0f));

		} else {
			/* left hemisphere */
			constrained_roll = math::constrain(ctl_data.roll, math::radians(-100.0f), math::radians(-180.0f));
		}
	}

	/* input conditioning */
	float airspeed = constrain_airspeed(ctl_data.airspeed, ctl_data.airspeed_min, ctl_data.airspeed_max);

	/* Calculate desired body fixed y-axis angular rate needed to compensate for roll angle.
	   For reference see Automatic Control of Aircraft and Missiles by John H. Blakelock, pg. 175
	   Availible on google books 8/11/2015: 
	   https://books.google.com/books?id=ubcczZUDCsMC&pg=PA175#v=onepage&q&f=false*/
	float body_fixed_turn_offset = (fabsf((CONSTANTS_ONE_G / airspeed) *
				  		tanf(constrained_roll) * sinf(constrained_roll)));

	if (inverted) {
		body_fixed_turn_offset = -body_fixed_turn_offset;
	}

	/* Finally add the turn offset to your bodyrate setpoint*/
	_bodyrate_setpoint += body_fixed_turn_offset;


	_rate_error = _bodyrate_setpoint - ctl_data.pitch_rate;

	if (!lock_integrator && _k_i > 0.0f) {

		float id = _rate_error * dt * ctl_data.scaler;

		/*
		 * anti-windup: do not allow integrator to increase if actuator is at limit
		 */
		if (_last_output < -1.0f) {
			/* only allow motion to center: increase value */
			id = math::max(id, 0.0f);

		} else if (_last_output > 1.0f) {
			/* only allow motion to center: decrease value */
			id = math::min(id, 0.0f);
		}

		_integrator += id;
	}

    _dif_rate_error = _rate_error - _last_rate_error;
    _last_rate_error = _rate_error;

	/* integrator limit */
	//xxx: until start detection is available: integral part in control signal is limited here
	float integrator_constrained = math::constrain(_integrator * _k_i, -_integrator_max, _integrator_max);

	/* Apply PI rate controller and store non-limited output */
	_last_output = _bodyrate_setpoint * _k_ff * ctl_data.scaler +
		       _rate_error * _k_p * ctl_data.scaler * ctl_data.scaler
		       + integrator_constrained;  //scaler is proportional to 1/airspeed
//	warnx("pitch: _integrator: %.4f, _integrator_max: %.4f, airspeed %.4f, _k_i %.4f, _k_p: %.4f", (double)_integrator, (double)_integrator_max, (double)airspeed, (double)_k_i, (double)_k_p);
//	warnx("roll: _last_output %.4f", (double)_last_output);
    fp = open(PX4_ROOTFSDIR"/fs/microsd/log/output_pitch.csv", O_CREAT | O_WRONLY | O_DSYNC | O_APPEND);
    int bytes = sprintf(buffer, "%.6f,%.6f,%.6f\n", (double)_rate_error, (double)_dif_rate_error, (double)math::constrain(_last_output, -1.0f, 1.0f));
    write(fp, buffer, bytes);
    close(fp);
	return math::constrain(_last_output, -1.0f, 1.0f);
}