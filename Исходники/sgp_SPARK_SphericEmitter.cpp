void SphericEmitter::computeMatrix()
{
	tDirection.Normalize();
	if( (tDirection.x == 0.0f) && (tDirection.y == 0.0f) )
	{
			
		matrix[0] = tDirection.z;
		matrix[1] = 0.0f;
		matrix[2] = 0.0f;
		matrix[3] = 0.0f;
		matrix[4] = tDirection.z;
		matrix[5] = 0.0f;
		matrix[6] = 0.0f;
		matrix[7] = 0.0f;
		matrix[8] = tDirection.z;
	}
	else
	{
		Vector3D axis;
		axis.Cross( tDirection, Vector3D(0.0f,0.0f,1.0f) );

		float cosA = tDirection.z;
		float sinA = -axis.GetLength();
		axis /= -sinA;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		matrix[0] = x * x + cosA * (1.0f - x * x);
		matrix[1] = x * y * (1.0f - cosA) - z * sinA;
		matrix[2] = tDirection.x;
		matrix[3] = x * y * (1.0f - cosA) + z * sinA;
		matrix[4] = y * y + cosA * (1.0f - y * y);
		matrix[5] = tDirection.y;
		matrix[6] = x * z * (1.0f - cosA) - y * sinA;
		matrix[7] = y * z * (1.0f - cosA) + x * sinA;
		matrix[8] = tDirection.z;
	}
}