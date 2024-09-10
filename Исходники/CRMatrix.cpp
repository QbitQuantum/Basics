// Euler degress(X->Y->Z) <= matrix[4][4]
void CRMatrixMat4x42UnityEulerZXYDegrees3(float *degrees, float matrix[4][4]) {
	float x = asinf(-matrix[1][2]);
	float y = 0;
	float z = 0;
	
	if (cos(x) == 0) {
		y = atan2f(-matrix[2][0], matrix[0][0]);
		z = 0;
	}
	else {
		y = atan2f(matrix[0][2], matrix[2][2]);
		z = atan2f(matrix[1][0], matrix[1][1]);
	}
	
	degrees[0] = x;
	degrees[1] = -y;
	degrees[2] = -z;
}