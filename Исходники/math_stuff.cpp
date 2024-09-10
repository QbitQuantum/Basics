// BitStream::WriteOrthMatrix
void GetOrthMatrix(float m00, float m01, float m02,
				   float m10, float m11, float m12,
				   float m20, float m21, float m22,
				   float *fOutW, float *fOutX, float *fOutY, float *fOutZ)
{
	double qw;
	double qx;
	double qy;
	double qz;

#ifdef _MSC_VER
#pragma warning(disable:4100)   // m10, m01 : unreferenced formal parameter
#endif

	// Convert matrix to quat
	// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
	float sum;
	sum = 1 + m00 + m11 + m22;
	if (sum < 0.0f) sum=0.0f;
	qw = sqrt( sum  ) / 2; 
	sum = 1 + m00 - m11 - m22;
	if (sum < 0.0f) sum=0.0f;
	qx = sqrt( sum  ) / 2; 
	sum = 1 - m00 + m11 - m22;
	if (sum < 0.0f) sum=0.0f;
	qy = sqrt( sum  ) / 2; 
	sum = 1 - m00 - m11 + m22;
	if (sum < 0.0f) sum=0.0f;
	qz = sqrt( sum  ) / 2;
	if (qw < 0.0) qw=0.0;
	if (qx < 0.0) qx=0.0;
	if (qy < 0.0) qy=0.0;
	if (qz < 0.0) qz=0.0;
	qx = _copysign( qx, m21 - m12 );
	qy = _copysign( qy, m02 - m20 );
	qz = _copysign( qz, m10 - m01 );
	*fOutW = (float)qw;
	*fOutX = (float)qx;
	*fOutY = (float)qy;
	*fOutZ = (float)qz;
}