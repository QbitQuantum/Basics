void GetRay(int sx, int sy, Vector3 &orig, Vector3 &dir)
{
	const float x =  ( (sx * 2.0F / WINSIZE_X ) - 1.0F );
	const float y = -( (sy * 2.0F / WINSIZE_Y) - 1.0F );

	Vector3 v;
	v.x = x / g_matProj._11;
	v.y = y / g_matProj._22;
	v.z =  1.0F;

	Matrix44 m = g_matView.Inverse();

	dir.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	dir.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	dir.z = v.x * m._13 + v.y * m._23 + v.z * m._33;

	orig.x = m._41;
	orig.y = m._42;
	orig.z = m._43;
}