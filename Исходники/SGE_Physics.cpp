Vector2 Physics_Response(const float dt, const Vector2& src, const Vector2& contact, const Vector2& velocity, const float restitution/* = 2.0f*/)
{
	if (dt == 0.0f)
	{
		return Vector2(0.f, 0.f);
	}

	Vector2 normal = contact - src;
	normal.Normalize();

	Vector2 vel_dt = velocity * dt;
	SGE::Graphics_DebugLine(src, src + vel_dt, 0xAAAAFF);
	SGE::Graphics_DebugLine(contact, src, 0x00FF00);

	float dot = SGE::Math_Dot(vel_dt, normal);
	Vector2 A = (normal * restitution) * dot;

	SGE::Graphics_DebugLine(contact, contact + A, 0xFFFFFF);

	Vector2 X = vel_dt - A;
	SGE::Graphics_DebugLine(src, src + X, 0xFF0000);

	Vector2 response_vel = X * (1.f/dt);
	return response_vel;
}