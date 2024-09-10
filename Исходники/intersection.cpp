void R_SetLightProject(idPlane lightProject[4], 
					   const idVec3 &origin, 
					   const idVec3 &target,
					   idVec3 &right, 
					   idVec3 &up,
					   const idVec3 &start, 
					   const idVec3 &stop)
{
	float		dist;
	float		scale;
	float		rLen, uLen;
	idVec3		normal;
	float		ofs;
	idVec3		startGlobal;
	idVec4		targetGlobal;

	rLen = right.Normalize();
	uLen = up.Normalize();
	normal = up.Cross(right);
	normal.Normalize();

	dist = target * normal; //  - (origin * normal);
	if(dist < 0)
	{
		dist = -dist;
		normal = -normal;
	}

	scale = (0.5f * dist) / rLen;
	right *= scale;
	scale = -(0.5f * dist) / uLen;
	up *= scale;

	lightProject[2] = normal;
	lightProject[2][3] = -(origin * lightProject[2].Normal());

	lightProject[0] = right;
	lightProject[0][3] = -(origin * lightProject[0].Normal());

	lightProject[1] = up;
	lightProject[1][3] = -(origin * lightProject[1].Normal());

	// now offset to center
	targetGlobal.ToVec3() = target + origin;
	targetGlobal[3] = 1;
	ofs = 0.5f - (targetGlobal * lightProject[0].ToVec4()) / (targetGlobal * lightProject[2].ToVec4());
	lightProject[0].ToVec4() += ofs * lightProject[2].ToVec4();
	ofs = 0.5f - (targetGlobal * lightProject[1].ToVec4()) / (targetGlobal * lightProject[2].ToVec4());
	lightProject[1].ToVec4() += ofs * lightProject[2].ToVec4();

	// set the falloff vector
	normal = stop - start;
	dist = normal.Normalize();
	if (dist <= 0)
	{
		dist = 1;
	}
	lightProject[3] = normal * (1.0f / dist);
	startGlobal = start + origin;
	lightProject[3][3] = -(startGlobal * lightProject[3].Normal());
}