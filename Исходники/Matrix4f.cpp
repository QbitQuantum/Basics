//----------------------------------------------------------------------------------------------------
Matrix4f Matrix4f::LookAtLHMatrix( Vector3f& eye, Vector3f& at, Vector3f& up )
{
	// This method is based on the method of the same name from the D3DX library.

	Matrix4f ret;

	Vector3f zaxis = at - eye; 
	zaxis.Normalize();
	
	Vector3f xaxis = up.Cross( zaxis );
	xaxis.Normalize();

	Vector3f yaxis = zaxis.Cross( xaxis );

	ret.m_afEntry[ 0] = xaxis.x;
	ret.m_afEntry[ 1] = yaxis.x;
	ret.m_afEntry[ 2] = zaxis.x;
	ret.m_afEntry[ 3] = 0.0f;

	ret.m_afEntry[ 4] = xaxis.y;
	ret.m_afEntry[ 5] = yaxis.y;
	ret.m_afEntry[ 6] = zaxis.y;
	ret.m_afEntry[ 7] = 0.0f;

	ret.m_afEntry[ 8] = xaxis.z;
	ret.m_afEntry[ 9] = yaxis.z;
	ret.m_afEntry[10] = zaxis.z;
	ret.m_afEntry[11] = 0.0f;

	ret.m_afEntry[12] = -(xaxis.Dot(eye));
	ret.m_afEntry[13] = -(yaxis.Dot(eye));
	ret.m_afEntry[14] = -(zaxis.Dot(eye));
	ret.m_afEntry[15] = 1.0f;

	return( ret );
}