void CCameraRayScan::ShootRays(const Vec3 &rayPos, const Vec3 &rayDir, IPhysicalEntity **pSkipEnts, int numSkipEnts)
{

	//shoot rays for all ray_hits
	const Vec3 dirNorm = rayDir.normalized();
	const Vec3 right = dirNorm.Cross(Vec3Constants<float>::fVec3_OneZ);
	const Vec3 rightOff = right * 0.15f;
	const Vec3 rightDir = right * 0.15f;
	const float len = rayDir.len() * RAY_SCAN_BUFFER_SCALE; //add some distance to be sure that the view is free

	const Vec3 rayPos2 = rayPos + (dirNorm * RAY_SCAN_OFFSET_DISTANCE); //move the rays away from the head to prevent clipping

	//center ray
	Vec3 tempPos = rayPos2;
	Vec3 tempDir = dirNorm;
	ShootRayInt(eRAY_CENTER, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm - rightDir + g_vRayUpDir).normalized();
	tempPos = rayPos2 - rightOff + g_vRayUpOffset;
	ShootRayInt(eRAY_TOP_LEFT, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm + rightDir + g_vRayUpDir).normalized();
	tempPos = rayPos2 + rightOff + g_vRayUpOffset;
	ShootRayInt(eRAY_TOP_RIGHT, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm - rightDir - g_vRayUpDir).normalized();
	tempPos = rayPos2 - rightOff - g_vRayUpOffset;
	ShootRayInt(eRAY_BOTTOM_LEFT, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm + rightDir - g_vRayUpDir).normalized();
	tempPos = rayPos2 + rightOff - g_vRayUpOffset;
	ShootRayInt(eRAY_BOTTOM_RIGHT, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm + g_vRayUpDir).normalized();
	tempPos = rayPos2 + g_vRayUpOffset * 2.0f;
	ShootRayInt(eRAY_TOP_CENTER, tempPos, tempDir, len, pSkipEnts, numSkipEnts);

	tempDir = (dirNorm - g_vRayUpDir).normalized();
	tempPos = rayPos2 - g_vRayUpOffset * 2.0f;
	ShootRayInt(eRAY_BOTTOM_CENTER, tempPos, tempDir, len, pSkipEnts, numSkipEnts);
}