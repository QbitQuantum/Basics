/*
================
hhCameraInterpolator::DetermineIdealRotation
================
*/
idQuat hhCameraInterpolator::DetermineIdealRotation( const idVec3& idealUpVector, const idVec3& viewDir, const idMat3& untransformedViewAxis ) {
	idMat3 mat;
	idVec3 newViewVector( viewDir );

	newViewVector.ProjectOntoPlane( idealUpVector );
	if( newViewVector.LengthSqr() < VECTOR_EPSILON ) {
		newViewVector = -Sign( newViewVector * idealUpVector );
	}

	newViewVector.Normalize();
	mat[0] = newViewVector;
	mat[1] = idealUpVector.Cross( newViewVector );
	mat[2] = idealUpVector;

	mat = untransformedViewAxis.Transpose() * mat;
	return mat.ToQuat();
}