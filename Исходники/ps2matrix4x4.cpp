void Matrix4x4::LookAt(const Vector4 & vFrom, const Vector4 & vTo, const Vector4 & vUp)
{
	Vector4 vZ = Normalise(vFrom - vTo);
	//vZ.DumpVector4("vZ");
	Vector4 vX = Normalise(vUp.Cross(vZ));
	//vX.DumpVector4("vX");
	Vector4 vY = vZ.Cross(vX);
	//vY.DumpVector4("vY");

    elem[0][0] = vX.x;	elem[0][1] = vY.x;	elem[0][2] = vZ.x;	elem[0][3] = 0;
	elem[1][0] = vX.y;	elem[1][1] = vY.y;	elem[1][2] = vZ.y;	elem[1][3] = 0;
	elem[2][0] = vX.z;	elem[2][1] = vY.z;	elem[2][2] = vZ.z;	elem[2][3] = 0;

	elem[3][0] = -vX.Dot3(vFrom);
	elem[3][1] = -vY.Dot3(vFrom);
	elem[3][2] = -vZ.Dot3(vFrom);
	elem[3][3] = 1;
}