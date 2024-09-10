bool SailMotor::move_to_angle(float degrees, float reference, int& feedback, int& num_rounds) {
	
    float position;
    int target = 0;

	if(degrees <= 180 && degrees >= -180) {
		// get feedback
        epos_get_actual_position(AV_SAIL_NODE_ID);
        feedback = epos_read.node[AV_SAIL_NODE_ID-1].actual_position;
        position = (feedback / (AV_SAIL_TICKS_PER_DEGREE))-reference;

       // num_rounds = (feedback + 180 * AV_SAIL_TICKS_PER_DEGREE) / (360 * AV_SAIL_TICKS_PER_DEGREE);
	//	num_rounds = (int)round((position+180.0*sign(position))/360.0);
		num_rounds = (int)round((position)/360.0);
		//rtx_message("num_ro: %d, feedback: %d", num_rounds, feedback);
		//num_rounds = (position+180.0)/360.0;
		position = remainder(position, 360.0);
        if(fabs(degrees - position) > 180.0)
        {
            num_rounds -= 1*sign(remainder((position - degrees),360.0));
        }
//rtx_message("pos: %f, num_ro: %d", position, num_rounds);
		// Go to position
        target = (int)round(AV_SAIL_TICKS_PER_DEGREE * (degrees + reference + num_rounds*360));
        epos_set_target_position(AV_SAIL_NODE_ID, target);
//		rtx_message("num_ro: %d, position: %f, target: %f", num_rounds, position, target/AV_SAIL_TICKS_PER_DEGREE*1.0);
		//rtx_message("current: %f; %d, goal: %f; %d", position, feedback, degrees, target);
		epos_activate_position(AV_SAIL_NODE_ID);
	}
	else {
		rtx_message("WARNING: A Sail angle beyond +-180 deg has been asked for. (at %f) Skipping...", degrees);
		return false;
	}

#if 0
	if(degrees <= AV_MAX_SAIL_ANGLE && degrees >= -AV_MAX_SAIL_ANGLE) {
		// Go to position
		epos_set_target_position(AV_SAIL_NODE_ID,(int)round((degrees+reference)*AV_SAIL_TICKS_PER_DEGREE));
		epos_activate_position(AV_SAIL_NODE_ID);

		// and get feedback
        epos_get_actual_position(AV_SAIL_NODE_ID);
        feedback = epos_read.node[AV_SAIL_NODE_ID-1].actual_position;
	}
	else {
		rtx_message("WARNING: A Sail angle beyond the max sail angle has been asked for. (at %f) Skipping...", degrees);
		return false;
	}
#endif

	return true;

}