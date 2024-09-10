inline float Vector2F::Angle (Vector2F const& other) const
{
	// P.Q = ||P|| * ||Q|| * cos(theta)
	// P.Q/(||P|| * ||Q||) = cos(theta)
	// Therefore, theta = arccos( P.Q/(||P|| * ||Q||) )
	return acos(Dot(other)/(Norm() * other.Norm()));
}