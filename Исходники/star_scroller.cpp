void star_scroller::update(float t)
{
	float f = t * 0.1f;
	float x = fmod(3*(sin(1.5f*f+3) + 1.0f), 2.0f);
	float y = fmod(3*(sin(1.7f*f+1) + 1.0f), 2.0f);
	float z = fmod(5*(sin(2.3f*f) + 1.0f), 1.0f);
	state_set_->set_vertex_program_parameter(0, vector4f(x, y, z, 1.0));

	size_t frame_i = 0;
	while(star_count_frames[frame_i].time < t)
		++frame_i;
	f = (t - star_count_frames[frame_i-1].time)
		/ (star_count_frames[frame_i].time - star_count_frames[frame_i-1].time);
	set_visible_stars(star_count_frames[frame_i-1].count +
		f*(star_count_frames[frame_i].count - star_count_frames[frame_i-1].count));
	//set_visible_stars(1);

	//std::cout << "visible_stars = " << visible_stars_ << std::endl;
	state_set_->set_vertex_range(0, visible_stars_*3);
}