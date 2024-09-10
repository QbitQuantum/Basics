Vector4F operator*(Matrix4x4F & A, Vector4F & v)
{
	return Vector4F(
		A.m[0][0]*v.x + A.m[0][1]*v.y + A.m[0][2]*v.z + A.m[0][3]*v.w,
		A.m[1][0]*v.x + A.m[1][1]*v.y + A.m[1][2]*v.z + A.m[1][3]*v.w,
		A.m[2][0]*v.x + A.m[2][1]*v.y + A.m[2][2]*v.z + A.m[2][3]*v.w,
		A.m[3][0]*v.x + A.m[3][1]*v.y + A.m[3][2]*v.z + A.m[3][3]*v.w);
}