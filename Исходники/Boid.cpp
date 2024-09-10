Vec2 Boid::Steer(const Vec2& target) const
{
	if (!target.IsZero())
	{
		Vec2 dir = target.Normalize();
		dir *= m_MaxSpeed;
		Vec2 steer = dir - GetVelocity();
		steer = steer.Clamp(m_MaxSteeringForce);
		return steer;
	}
	else
		return Vec2();
}