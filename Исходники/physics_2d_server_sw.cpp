void Physics2DServerSW::body_set_axis_velocity(RID p_body, const Vector2 &p_axis_velocity) {

	Body2DSW *body = body_owner.get(p_body);
	ERR_FAIL_COND(!body);

	Vector2 v = body->get_linear_velocity();
	Vector2 axis = p_axis_velocity.normalized();
	v -= axis * axis.dot(v);
	v += p_axis_velocity;
	body->set_linear_velocity(v);
	body->wakeup();
};