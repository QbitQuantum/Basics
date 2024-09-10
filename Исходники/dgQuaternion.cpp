dgQuaternion::dgQuaternion (const dgMatrix& matrix)
{
	enum QUAT_INDEX
	{
		X_INDEX=0,
		Y_INDEX=1,
		Z_INDEX=2
	};
	static QUAT_INDEX QIndex [] = {Y_INDEX, Z_INDEX, X_INDEX};

	dgFloat32 trace = matrix[0][0] + matrix[1][1] + matrix[2][2];
	if (trace > dgFloat32(0.0f)) {
		trace = dgSqrt (trace + dgFloat32(1.0f));
		m_q0 = dgFloat32 (0.5f) * trace;
		trace = dgFloat32 (0.5f) / trace;
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

		trace = dgFloat32(1.0f) + matrix[i][i] - matrix[j][j] - matrix[k][k];
		trace = dgSqrt (trace);

		dgFloat32* const ptr = &m_q1;
		ptr[i] = dgFloat32 (0.5f) * trace;
		trace  = dgFloat32 (0.5f) / trace;
		m_q0   = (matrix[j][k] - matrix[k][j]) * trace;
		ptr[j] = (matrix[i][j] + matrix[j][i]) * trace;
		ptr[k] = (matrix[i][k] + matrix[k][i]) * trace;
	}

#ifdef _DEBUG
	dgMatrix tmp (*this, matrix.m_posit);
	dgMatrix unitMatrix (tmp * matrix.Inverse());
	for (dgInt32 i = 0; i < 4; i ++) {
		dgFloat32 err = dgAbsf (unitMatrix[i][i] - dgFloat32(1.0f));
		dgAssert (err < dgFloat32 (1.0e-2f));
	}

	dgFloat32 err = dgAbsf (DotProduct(*this) - dgFloat32(1.0f));
	dgAssert (err < dgFloat32(dgEPSILON * 100.0f));
#endif
}