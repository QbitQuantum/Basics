static PX_FORCE_INLINE Ps::IntBool planeBoxOverlap(const PxVec3& normal, PxReal d, const PxVec3& maxbox)
{
	PxVec3 vmin,vmax;

	if (normal.x>0.0f)
	{
		vmin.x = -maxbox.x;
		vmax.x = maxbox.x;
	}
	else
	{
		vmin.x = maxbox.x;
		vmax.x = -maxbox.x;
	}

	if (normal.y>0.0f)
	{
		vmin.y = -maxbox.y;
		vmax.y = maxbox.y;
	}
	else
	{
		vmin.y = maxbox.y;
		vmax.y = -maxbox.y;
	}

	if (normal.z>0.0f)
	{
		vmin.z = -maxbox.z;
		vmax.z = maxbox.z;
	}
	else
	{
		vmin.z = maxbox.z;
		vmax.z = -maxbox.z;
	}

	if( normal.dot(vmin) + d >  0.0f) return Ps::IntFalse;
	if( normal.dot(vmax) + d >= 0.0f) return Ps::IntTrue;
	return Ps::IntFalse;
}