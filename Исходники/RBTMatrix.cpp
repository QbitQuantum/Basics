/**
Constructs a rigid-body transformation matrix from an axis, an angle and a translation vector.

@param axis			The rotation axis
@param angle		The rotation angle (in radians, NOT degrees)
@param translation	The translation vector
*/
RBTMatrix_Ptr RBTMatrix::from_axis_angle_translation(Vector3d axis, double angle, const Vector3d& translation)
{
	if(fabs(axis.length_squared() - 1) > SMALL_EPSILON)
	{
		if(axis.length_squared() > EPSILON*EPSILON) axis.normalize();
		else throw Exception("RBTMatrix::from_axis_angle_translation: Can't rotate about a zero-length axis");
	}

	RBTMatrix_Ptr ret(new RBTMatrix);
	double (&M)[3][4] = ret->m;

	double c = cos(angle);
	double s = sin(angle);
	double t = 1 - c;

	const double& x = axis.x;
	const double& y = axis.y;
	const double& z = axis.z;

	// See p.62 of "Mathematics for 3D Game Programming & Computer Graphics" (Eric Lengyel).
	M[0][0] = t*x*x + c;		M[0][1] = t*x*y - s*z;		M[0][2] = t*x*z + s*y;		M[0][3] = translation.x;
	M[1][0] = t*x*y + s*z;		M[1][1] = t*y*y + c;		M[1][2] = t*y*z - s*x;		M[1][3] = translation.y;
	M[2][0] = t*x*z - s*y;		M[2][1] = t*y*z + s*x;		M[2][2] = t*z*z + c;		M[2][3] = translation.z;

	return ret;
}