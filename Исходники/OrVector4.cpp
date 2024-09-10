// ******************************************************************************** //
// The spherical interpolation for union quaternions
Quaternion OrE::Math::Slerp(const Quaternion& a, const Quaternion& b, const float t)
{
	float fOmega = Arccos( Clamp(a.Dot(b), -1.0f, 1.0f) );
	float f1 = Sin( fOmega * (1.0f-t) );
	float f2 = Sin( fOmega * t );
	return Quaternion( a.r*f1+b.r*f2, a.i*f1+b.i*f2, a.j*f1+b.j*f2, a.k*f1+b.k*f2 );
}