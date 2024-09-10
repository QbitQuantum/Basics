b2Vec2 BilliardBall::angularToLinear(Vec3 m_angularVelocity) {
	b2Vec2 m_velocity;
	Vec3 r = Vec3(0, 0, -CIRCLE_RADIUS);

	r.cross(m_angularVelocity);
	m_velocity = b2Vec2(ANGULAR_POWER * r.x, ANGULAR_POWER * r.y);

	return m_velocity;
}