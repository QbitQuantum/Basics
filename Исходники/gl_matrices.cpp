void glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
	XMMATRIX tmp = XMMatrixOrthographicOffCenterLH(left, right, bottom, top, zNear, zFar);
	CURRENT_MATRIX_STACK = tmp * CURRENT_MATRIX_STACK;

	current_matrix->dirty = 1;
}