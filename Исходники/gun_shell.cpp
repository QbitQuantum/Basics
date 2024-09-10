gun_shell::gun_shell(game& gm_, const vector3& pos, angle direction, angle elevation,
	double initial_velocity, double damage)
	: sea_object(gm_, "gun_shell.ddxml")
{
	orientation = quaternion::rot(-direction.value(), 0, 0, 1);
	mass = 20;
	mass_inv = 1.0/mass;
	linear_momentum = mass * orientation.rotate(vector3(0,
		elevation.cos() * initial_velocity,
		elevation.sin() * initial_velocity));
	// set off initial pos. like 0.5 seconds after firing, to avoid
	// collision with parent
	position = pos + linear_momentum * (mass_inv * 0.5);
	angular_momentum = vector3();
	compute_helper_values();
	oldpos = position;
	damage_amount = damage;

	log_info("shell created");
}