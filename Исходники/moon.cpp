void moon::display(const vector3 &moon_pos, const vector3 &sun_pos, double max_view_dist) const
{
	vector3 moon_dir = moon_pos.normal();
	double moon_size = max_view_dist/20;
	float moon_azimuth = atan2(-moon_dir.y, moon_dir.x);
	float moon_elevation = asin(moon_dir.z);

	glsl_moon->use();
	glsl_moon->set_gl_texture(*map_diffuse, loc_diffcol, 0);
	glsl_moon->set_gl_texture(*map_normal, loc_nrml, 1);
	//	transform light into object space
	matrix4 roth = matrix4::rot_z(-RAD_TO_DEG(moon_azimuth));
	matrix4 rotv = matrix4::rot_y(-RAD_TO_DEG(moon_elevation));
	matrix4 model_mat = roth*rotv;
	vector3 l = model_mat.inverse() * sun_pos;
	vector3 nl = vector3(-l.y, l.z, -l.x).normal();	//	OpenGL coordinates
	glsl_moon->set_uniform(loc_lightdir, nl);

	//	render moon
	glPushMatrix();
	model_mat.multiply_gl();
	glTranslated(0.95*max_view_dist, 0, 0);

	primitives::textured_quad(vector3f( 0,  moon_size,  moon_size),
				  vector3f( 0, -moon_size,  moon_size),
				  vector3f( 0, -moon_size, -moon_size),
				  vector3f( 0,  moon_size, -moon_size),
				  *map_diffuse).render_plain();
	glPopMatrix();
}