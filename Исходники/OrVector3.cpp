// ******************************************************************************** //
// The spherical interpolation applies only to normal vectors
Vec3 OrE::Math::Slerp(const Vec3& v1, const Vec3& v2, const float t)
{
	float fOmega = Arccos( Clamp(v1.Dot(v2), -1.0f, 1.0f) );
	float f1 = Sin( fOmega * (1.0f-t) );
	float f2 = Sin( fOmega * t );
	return Vec3( v1.x*f1+v2.x*f2, v1.y*f1+v2.y*f2, v1.z*f1+v2.z*f2 ).Normalize();
}