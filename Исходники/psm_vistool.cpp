void	draw_stuff(const controls& c, float density)
{
	float	mx = c.m_mouse_x - 500.0f;
	float	my = 500.0f - c.m_mouse_y;
	vec3	mouse_pos(mx, my, 0);

	if (c.m_mouse_right)
	{
		// Re-compute light direction.
		s_light_direction = mouse_pos - s_light_arrow_spot;
		s_light_direction.normalize();

		// Direction perpendicular to the light.
		s_light_right = vec3(s_light_direction.y, -s_light_direction.x, 0);

		// Draw a white line to the mouse, so the user can see
		// what they're orbiting around.
		glColor3f(1, 1, 1);
		draw_segment(s_light_arrow_spot, mouse_pos);
	}

	if (c.m_mouse_left_click)
	{
		// Add or delete an occluder.

		// If we're on an occluder, then delete it.
		bool	deleted = false;
		for (int i = 0; i < s_occluders.size(); i++)
		{
			if (s_occluders[i].hit(mouse_pos))
			{
				// Remove this guy.
				s_occluders[i] = s_occluders.back();
				s_occluders.resize(s_occluders.size() - 1);
				deleted = true;
				break;
			}
		}

		if (!deleted)
		{
			// If we didn't delete, then the user want to
			// add an occluder.
			s_occluders.push_back(occluder(mouse_pos, 20));
		}
	}

	draw_light_arrow();
	draw_light_rays(density);
	draw_occluders();

	// Draw a line at the "near clip plane".
	glColor3f(0, 0, 1);
	draw_segment(vec3(-1000, s_viewer_y, 0), vec3(1000, s_viewer_y, 0));

	draw_frustum();
}