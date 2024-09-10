// Convert an orientation matrix to a pitch/yaw/roll vector.  Based on what
// Freelancer does for the save game.
Vector MatrixToEuler(const Matrix& mat)
{
	Vector x = { mat.data[0][0], mat.data[1][0], mat.data[2][0] };
	Vector y = { mat.data[0][1], mat.data[1][1], mat.data[2][1] };
	Vector z = { mat.data[0][2], mat.data[1][2], mat.data[2][2] };

	Vector vec;
	float h = (float)_hypot( x.x, x.y );
	if (h > 1/524288.0f)
	{
		vec.x = degrees( atan2f(  y.z, z.z ) );
		vec.y = degrees( atan2f( -x.z, h   ) );
		vec.z = degrees( atan2f(  x.y, x.x ) );
	}
	else
	{
		vec.x = degrees( atan2f( -z.y, y.y ) );
		vec.y = degrees( atan2f( -x.z, h   ) );
		vec.z = 0;
	}
	return vec;
}