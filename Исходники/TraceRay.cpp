/**
 * helper for TestTrajectoryCone
 * @return true if object <o> is in the firing trajectory, false otherwise
 */
inline bool TestTrajectoryConeHelper(
	const float3& from,
	const float3& flatdir,
	float length,
	float linear,
	float quadratic,
	float spread,
	float baseSize,
	const CSolidObject* o)
{
	const CollisionVolume* cv = o->collisionVolume;
	float3 dif = (o->midPos + cv->GetOffsets()) - from;
	const float3 flatdif(dif.x, 0, dif.z);
	float closeFlatLength = flatdif.dot(flatdir);

	if (closeFlatLength <= 0)
		return false;
	if (closeFlatLength > length)
		closeFlatLength = length;

	if (fabs(linear - quadratic * closeFlatLength) < 0.15f) {
		// relatively flat region -> use approximation
		dif.y -= (linear + quadratic * closeFlatLength) * closeFlatLength;

		// NOTE: overly conservative for non-spherical volumes
		const float3 closeVect = dif - flatdir * closeFlatLength;
		const float r = cv->GetBoundingRadius() + spread * closeFlatLength + baseSize;
		if (closeVect.SqLength() < r * r) {
			return true;
		}
	} else {
		float3 newfrom = from + flatdir * closeFlatLength;
		newfrom.y += (linear + quadratic * closeFlatLength) * closeFlatLength;
		float3 dir = flatdir;
		dir.y = linear + quadratic * closeFlatLength;
		dir.Normalize();

		dif = (o->midPos + cv->GetOffsets()) - newfrom;
		const float closeLength = dif.dot(dir);

		// NOTE: overly conservative for non-spherical volumes
		const float3 closeVect = dif - dir * closeLength;
		const float r = cv->GetBoundingRadius() + spread * closeFlatLength + baseSize;
		if (closeVect.SqLength() < r * r) {
			return true;
		}
	}
	return false;
}