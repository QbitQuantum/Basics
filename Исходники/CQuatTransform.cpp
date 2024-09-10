// Spherical linear interpolation of two quaternion-transforms q0 and q1, with parameter t, 
// result in qt. Only the quaternion uses slerp, position and scaling use lerp
// Non-member function
void Slerp
(
	const CQuatTransform& q0,
	const CQuatTransform& q1,
	const TFloat32        t,
	CQuatTransform&       qt
)
{
	// Calculate lerp for position and scale
	qt.pos = q0.pos*(1.0f-t) + q1.pos*t;
	qt.scale = q0.scale*(1.0f-t) + q1.scale*t;

	// Call slerp function for quaternion rotation
	Slerp( q0.quat, q1.quat, t, qt.quat );
}