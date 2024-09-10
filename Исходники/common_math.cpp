CVector3 ReflectionVector(const CVector3 &normal, const CVector3 &incident)
{
	return incident - normal * incident.Dot(normal) * 2.0;
}