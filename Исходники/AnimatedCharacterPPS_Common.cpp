Vec3 CAnimatedCharacter::RemovePenetratingComponent(const Vec3& v, const Vec3& n) const
{
	float penetration = n.Dot(v);
	if (penetration >= 0.0f)
		return v;

	return (v - n * penetration);
}