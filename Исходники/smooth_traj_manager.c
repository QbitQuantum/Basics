void smooth_traj_goto_target(struct smooth_traj_dest* next_point, float target_x, float target_y)
{
	// Compute the angle and distance to send to the control system
	//float angle_ref, remaining_dist;
	// if the robot is close to the end, and he has to have a specified angle
	/*if ((next_point_distance < SMOOTH_TRAJ_DEFAULT_PRECISION_D_MM && !IS_UNDEFINED_ANGLE(next_point->a))
			&& (next_id == traj.last_id || (next_id != traj.last_id && ABS(next_point->a - position_get_angle_rad()) > SMOOTH_TRAJ_DEFAULT_PRECISION_A_RAD)))
	{
		angle_ref = next_point->a;
		remaining_dist = 0.f;
	}
	else*/

	float angle_ref = atan2f(-(target_x - position_get_x_mm()), target_y - position_get_y_mm());
	float remaining_dist = DISTANCE(position_get_x_mm(), position_get_y_mm(), target_x, target_y);


	//printf("tar x:%d  y:%d  dist:%f  a:%f\r\n", (int)target_x, (int)target_y, (double)next1_dist, (double)angle_ref);

	// go backward
	if (next_point->movement != NORMAL)
	{
		// just asserv in distance
		if (next_point->movement == BACKWARD){
			control_system_set_distance_mm_ref(position_get_distance_mm() - remaining_dist);
		}
		else if (next_point->movement == FORWARD){
			control_system_set_distance_mm_ref(position_get_distance_mm() + remaining_dist);
		}
	}
	else
	{
		control_system_set_distance_mm_ref(position_get_distance_mm() + remaining_dist);
		control_system_set_angle_rad_ref(angle_ref);
	}
}