void Node2D::move_x(float p_delta, bool p_scaled) {

	Transform2D t = get_transform();
	Vector2 m = t[0];
	if (!p_scaled)
		m.normalize();
	set_position(t[2] + m * p_delta);
}