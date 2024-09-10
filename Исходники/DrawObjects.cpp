static void computeBasis(const NxVec3& dir, NxVec3& right, NxVec3& up)
{
	// Derive two remaining vectors
	if(fabsf(dir.y)>0.9999f)	right = NxVec3(1.0f, 0.0f, 0.0f);
	else						right = (NxVec3(0.0f, 1.0f, 0.0f) ^ dir);
	right.normalize();
	up = dir ^ right;
}