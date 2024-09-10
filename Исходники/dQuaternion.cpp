dQuaternion::dQuaternion (const dMatrix &matrix)
{
	enum QUAT_INDEX
	{
		X_INDEX=0,
		Y_INDEX=1,
		Z_INDEX=2
	};
	static QUAT_INDEX QIndex [] = {Y_INDEX, Z_INDEX, X_INDEX};

	dFloat trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
	dAssert (((matrix[0] * matrix[1]) % matrix[2]) > 0.0f);

	if (trace > dFloat(0.0f)) {
		trace = dSqrt (trace + dFloat(1.0f));
		m_q0 = dFloat (0.5f) * trace;
		trace = dFloat (0.5f) / trace;
		m_q1 = (matrix[1][2] - matrix[2][1]) * trace;
		m_q2 = (matrix[2][0] - matrix[0][2]) * trace;
		m_q3 = (matrix[0][1] - matrix[1][0]) * trace;

	} else {
		QUAT_INDEX i = X_INDEX;
		if (matrix[Y_INDEX][Y_INDEX] > matrix[X_INDEX][X_INDEX]) {
			i = Y_INDEX;
		}
		if (matrix[Z_INDEX][Z_INDEX] > matrix[i][i]) {
			i = Z_INDEX;
		}
		QUAT_INDEX j = QIndex [i];
		QUAT_INDEX k = QIndex [j];

		trace = dFloat(1.0f) + matrix[i][i] - matrix[j][j] - matrix[k][k];
		trace = dSqrt (trace);

		dFloat* const ptr = &m_q1;
		ptr[i] = dFloat (0.5f) * trace;
		trace = dFloat (0.5f) / trace;
		m_q0 = (matrix[j][k] - matrix[k][j]) * trace;
		ptr[j] = (matrix[i][j] + matrix[j][i]) * trace;
		ptr[k] = (matrix[i][k] + matrix[k][i]) * trace;
	}

#if _DEBUG

	dMatrix tmp (*this, matrix.m_posit);
	dMatrix unitMatrix (tmp * matrix.Inverse());
	for (int i = 0; i < 4; i ++) {
		dFloat err = dAbs (unitMatrix[i][i] - dFloat(1.0f));
		dAssert (err < dFloat (1.0e-3f));
	}

	dFloat err = dAbs (DotProduct(*this) - dFloat(1.0f));
	dAssert (err < dFloat(1.0e-3f));
#endif

}