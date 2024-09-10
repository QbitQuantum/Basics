	state_set_->set_blending_mode(state_set::BLEND_ADD);
}

void cloud_object::remove_state_sets(batch* b)
{
	b->remove_state_set(state_set_);
}

// At time t:
// Change number of stars
// Change object
// Change color
// Change scale
cloud_object::key_frame cloud_object::key_frames[7] = {
	{ 0, NONE, vector4f(1.0f, 0.0f, 1.0f), 0.25f, 0},
	{ 68.0f, SPHERE, vector4f(0.1f, 0.0f, 1.0f), 0.25f, 50000},
	{ 90.0f, CUBE, vector4f(0.15f, 1.0f, 0.0f), 0.15f, 50000},
	{ 120.0f, TORUS, vector4f(0.1f, 0.1f, 1.0f), 0.35f, 50000},
	{ 140.0f, BROKEN_TORUS, vector4f(0.8f, 0.1f, 0.0f), 0.23f, 50000},
	{ 178.0f, NONE, vector4f(0.8f, 0.1f, 0.0f), 0.23f, 0},
	{ 1000.0f, NONE, vector4f(1.0f, 0.0f, 1.0f), 0.25f, 0}
};

void cloud_object::update(float t)
{
	float pitch = 1.0f;
	float roll = 1.3f;
	float yaw = 0.7f;

	float dt = t - last_time_;