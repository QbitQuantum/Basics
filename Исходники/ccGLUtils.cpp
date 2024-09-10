ccGLMatrixd ccGLUtils::GenerateGLRotationMatrixFromVectors(const CCVector3d& sourceVec, const CCVector3d& destVec)
{
	//we compute scalar prod between the two vectors
	double ps = sourceVec.dot(destVec);

	//we bound result (in case vecors are not exactly unit)
	if (ps > 1.0)
		ps = 1.0;
	else if (ps < -1.0)
		ps = -1.0;

	//we deduce angle from scalar prod
	double angle_deg = acos(ps) * CC_RAD_TO_DEG;

	//we compute rotation axis with scalar prod
	CCVector3d axis = sourceVec.cross(destVec);

	//we eventually compute the rotation matrix with axis and angle
	return GenerateGLRotationMatrixFromAxisAndAngle(axis, angle_deg);
}