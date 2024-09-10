void	mouse_motion_handler(float dx, float dy, int state)
// Handles mouse motion.
{
	bool	left_button = (state & 1) ? true : false;
	bool	right_button = (state & 4) ? true : false;

	float	f_speed = (1 << speed) / 200.f;

	if (left_button && right_button) {
		// Translate in the view plane.
		vec3	right = viewer_dir.cross(viewer_up);
		viewer_pos += right * dx * f_speed + viewer_up * -dy * f_speed;
		
	} else if (left_button) {
		// Rotate the viewer.
		viewer_theta += -dx / 100;
		while (viewer_theta < 0) viewer_theta += (float) (2 * M_PI);
		while (viewer_theta >= 2 * M_PI) viewer_theta -= (float) (2 * M_PI);

		viewer_phi += -dy / 100;
		const float	plimit = (float) (M_PI / 2);
		if (viewer_phi > plimit) viewer_phi = plimit;
		if (viewer_phi < -plimit) viewer_phi = -plimit;

		viewer_dir = vec3(1, 0, 0);
		viewer_up = vec3(0, 1, 0);
		
		viewer_dir = Geometry::Rotate(viewer_theta, viewer_up, viewer_dir);
		vec3	right = viewer_dir.cross(viewer_up);
		viewer_dir = Geometry::Rotate(viewer_phi, right, viewer_dir);
		viewer_up = Geometry::Rotate(viewer_phi, right, viewer_up);

	} else if (right_button) {
		// Translate the viewer.
		vec3	right = viewer_dir.cross(viewer_up);
		viewer_pos += right * dx * f_speed + viewer_dir * -dy * f_speed;
	}
}