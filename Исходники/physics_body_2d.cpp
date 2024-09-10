void RigidBody2D::set_axis_velocity(const Vector2& p_axis) {

	Vector2 v = state? state->get_linear_velocity() : linear_velocity;
	Vector2 axis = p_axis.normalized();
	v-=axis*axis.dot(v);
	v+=p_axis;
	if (state) {
		set_linear_velocity(v);
	} else {
		Physics2DServer::get_singleton()->body_set_axis_velocity(get_rid(),p_axis);
		linear_velocity=v;
	}
}