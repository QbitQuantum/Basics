fhRenderMatrix fhRenderMatrix::CreateLookAtMatrix( const idVec3& dir, const idVec3& up )
{
	idVec3 zaxis = (dir * -1).Normalized();
	idVec3 xaxis = up.Cross( zaxis ).Normalized();
	idVec3 yaxis = zaxis.Cross( xaxis );

	fhRenderMatrix m;
	m[0] = xaxis.x;
	m[1] = yaxis.x;
	m[2] = zaxis.x;

	m[4] = xaxis.y;
	m[5] = yaxis.y;
	m[6] = zaxis.y;

	m[8] = xaxis.z;
	m[9] = yaxis.z;
	m[10] = zaxis.z;
	return m;
}