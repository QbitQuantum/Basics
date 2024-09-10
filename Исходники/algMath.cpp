Quat nlerp( Quat q1, Quat q2, float t )
{
	float cosHalfTheta = QDotproduct( q1, q2 );
	if ( cosHalfTheta < 0 )
	{
		q1.w = -q1.w;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
	}

	Quat out = q1 + ( q2 - q1 ) * t;
	out.normalize();
	return out;
}