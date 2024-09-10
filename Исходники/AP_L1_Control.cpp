// update L1 control for waypoint navigation
void AP_L1_Control::update_waypoint(const struct Location &prev_WP, const struct Location &next_WP)
{

	struct Location _current_loc;
	float Nu;
	float xtrackVel;
	float ltrackVel;

    uint32_t now = AP_HAL::micros();
    float dt = (now - _last_update_waypoint_us) * 1.0e-6f;
    if (dt > 0.1) {
        dt = 0.1;
    }
    _last_update_waypoint_us = now;
    
	// Calculate L1 gain required for specified damping
	float K_L1 = 4.0f * _L1_damping * _L1_damping;

	// Get current position and velocity
    _ahrs.get_position(_current_loc);

	Vector2f _groundspeed_vector = _ahrs.groundspeed_vector();

	// update _target_bearing_cd
	_target_bearing_cd = get_bearing_cd(_current_loc, next_WP);
	
	//Calculate groundspeed
	float groundSpeed = _groundspeed_vector.length();
    if (groundSpeed < 0.1f) {
        // use a small ground speed vector in the right direction,
        // allowing us to use the compass heading at zero GPS velocity
        groundSpeed = 0.1f;
        _groundspeed_vector = Vector2f(cosf(_ahrs.yaw), sinf(_ahrs.yaw)) * groundSpeed;
    }

	// Calculate time varying control parameters
	// Calculate the L1 length required for specified period
	// 0.3183099 = 1/1/pipi
	_L1_dist = 0.3183099f * _L1_damping * _L1_period * groundSpeed;
	
	// Calculate the NE position of WP B relative to WP A
    Vector2f AB = location_diff(prev_WP, next_WP);
	
	// Check for AB zero length and track directly to the destination
	// if too small
	if (AB.length() < 1.0e-6f) {
		AB = location_diff(_current_loc, next_WP);
        if (AB.length() < 1.0e-6f) {
            AB = Vector2f(cosf(_ahrs.yaw), sinf(_ahrs.yaw));
        }
	}
	AB.normalize();

	// Calculate the NE position of the aircraft relative to WP A
    Vector2f A_air = location_diff(prev_WP, _current_loc);

	// calculate distance to target track, for reporting
	_crosstrack_error = A_air % AB;

	//Determine if the aircraft is behind a +-135 degree degree arc centred on WP A
	//and further than L1 distance from WP A. Then use WP A as the L1 reference point
		//Otherwise do normal L1 guidance
	float WP_A_dist = A_air.length();
	float alongTrackDist = A_air * AB;
	if (WP_A_dist > _L1_dist && alongTrackDist/MAX(WP_A_dist, 1.0f) < -0.7071f) 
    {
		//Calc Nu to fly To WP A
		Vector2f A_air_unit = (A_air).normalized(); // Unit vector from WP A to aircraft
		xtrackVel = _groundspeed_vector % (-A_air_unit); // Velocity across line
		ltrackVel = _groundspeed_vector * (-A_air_unit); // Velocity along line
		Nu = atan2f(xtrackVel,ltrackVel);
		_nav_bearing = atan2f(-A_air_unit.y , -A_air_unit.x); // bearing (radians) from AC to L1 point

	} else { //Calc Nu to fly along AB line
			
		//Calculate Nu2 angle (angle of velocity vector relative to line connecting waypoints)
		xtrackVel = _groundspeed_vector % AB; // Velocity cross track
		ltrackVel = _groundspeed_vector * AB; // Velocity along track
		float Nu2 = atan2f(xtrackVel,ltrackVel);
		//Calculate Nu1 angle (Angle to L1 reference point)
		float sine_Nu1 = _crosstrack_error/MAX(_L1_dist, 0.1f);
		//Limit sine of Nu1 to provide a controlled track capture angle of 45 deg
		sine_Nu1 = constrain_float(sine_Nu1, -0.7071f, 0.7071f);
		float Nu1 = asinf(sine_Nu1);

        // compute integral error component to converge to a crosstrack of zero when traveling
		// straight but reset it when disabled or if it changes. That allows for much easier
		// tuning by having it re-converge each time it changes.
		if (_L1_xtrack_i_gain <= 0 || !is_equal(_L1_xtrack_i_gain, _L1_xtrack_i_gain_prev)) {
		    _L1_xtrack_i = 0;
		    _L1_xtrack_i_gain_prev = _L1_xtrack_i_gain;
		} else if (fabsf(Nu1) < radians(5)) {
            _L1_xtrack_i += Nu1 * _L1_xtrack_i_gain * dt;

            // an AHRS_TRIM_X=0.1 will drift to about 0.08 so 0.1 is a good worst-case to clip at
            _L1_xtrack_i = constrain_float(_L1_xtrack_i, -0.1f, 0.1f);
		}

		// to converge to zero we must push Nu1 harder
        Nu1 += _L1_xtrack_i;

		Nu = Nu1 + Nu2;
		_nav_bearing = atan2f(AB.y, AB.x) + Nu1; // bearing (radians) from AC to L1 point		
	}	

    _prevent_indecision(Nu);
    _last_Nu = Nu;
			
	//Limit Nu to +-pi
	Nu = constrain_float(Nu, -1.5708f, +1.5708f);
	_latAccDem = K_L1 * groundSpeed * groundSpeed / _L1_dist * sinf(Nu);
	
	// Waypoint capture status is always false during waypoint following
	_WPcircle = false;
	
	_bearing_error = Nu; // bearing error angle (radians), +ve to left of track
}