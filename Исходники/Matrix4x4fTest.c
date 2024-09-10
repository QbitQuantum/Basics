static void testShear() {
	Matrix4x4f matrix;
	
	matrix = Matrix4x4f_shearedX(MATRIX4x4f_IDENTITY, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 0.0f, 0.0f, 0.0f,
	                                1.0f, 1.0f, 0.0f, 0.0f,
	                                1.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_shearedX(Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                                             VECTOR3f(0.0f, 0.0f, 1.0f),
	                                                             VECTOR3f(1.0f, 0.0f, 0.0f)),
	                             0.5f, -0.5f);
	assertMatrixApproximate(matrix, -0.5f, 0.0f, 1.0f, 0.0f,
	                                 1.0f, 0.0f, 0.0f, 0.0f,
	                                 0.5f, 1.0f, 0.0f, 0.0f,
	                                 0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_shearedY(MATRIX4x4f_IDENTITY, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 1.0f, 0.0f, 0.0f,
	                                0.0f, 1.0f, 0.0f, 0.0f,
	                                0.0f, 1.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_shearedY(Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                                             VECTOR3f(0.0f, 0.0f, 1.0f),
	                                                             VECTOR3f(1.0f, 0.0f, 0.0f)),
	                             0.5f, -0.5f);
	assertMatrixApproximate(matrix, 0.0f, -0.5f, 1.0f, 0.0f,
	                                1.0f,  0.5f, 0.0f, 0.0f,
	                                0.0f,  1.0f, 0.0f, 0.0f,
	                                0.0f,  0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_shearedZ(MATRIX4x4f_IDENTITY, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 1.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_shearedZ(Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                                             VECTOR3f(0.0f, 0.0f, 1.0f),
	                                                             VECTOR3f(1.0f, 0.0f, 0.0f)),
	                             0.5f, -0.5f);
	assertMatrixApproximate(matrix, 0.0f, 0.0f,  1.0f, 0.0f,
	                                1.0f, 0.0f,  0.5f, 0.0f,
	                                0.0f, 1.0f, -0.5f, 0.0f,
	                                0.0f, 0.0f,  0.0f, 1.0f, EPSILON);
	
	matrix = MATRIX4x4f_IDENTITY;
	Matrix4x4f_shearX(&matrix, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 0.0f, 0.0f, 0.0f,
	                                1.0f, 1.0f, 0.0f, 0.0f,
	                                1.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                         VECTOR3f(0.0f, 0.0f, 1.0f),
	                                         VECTOR3f(1.0f, 0.0f, 0.0f));
	Matrix4x4f_shearX(&matrix, 0.5f, -0.5f);
	assertMatrixApproximate(matrix, -0.5f, 0.0f, 1.0f, 0.0f,
	                                 1.0f, 0.0f, 0.0f, 0.0f,
	                                 0.5f, 1.0f, 0.0f, 0.0f,
	                                 0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = MATRIX4x4f_IDENTITY;
	Matrix4x4f_shearY(&matrix, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 1.0f, 0.0f, 0.0f,
	                                0.0f, 1.0f, 0.0f, 0.0f,
	                                0.0f, 1.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                         VECTOR3f(0.0f, 0.0f, 1.0f),
	                                         VECTOR3f(1.0f, 0.0f, 0.0f));
	Matrix4x4f_shearY(&matrix, 0.5f, -0.5f);
	assertMatrixApproximate(matrix, 0.0f, -0.5f, 1.0f, 0.0f,
	                                1.0f,  0.5f, 0.0f, 0.0f,
	                                0.0f,  1.0f, 0.0f, 0.0f,
	                                0.0f,  0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = MATRIX4x4f_IDENTITY;
	Matrix4x4f_shearZ(&matrix, 1.0f, 1.0f);
	assertMatrixApproximate(matrix, 1.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 1.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 1.0f, 0.0f,
	                                0.0f, 0.0f, 0.0f, 1.0f, EPSILON);
	
	matrix = Matrix4x4f_fromDirectionVectors(VECTOR3f(0.0f, 1.0f, 0.0f),
	                                         VECTOR3f(0.0f, 0.0f, 1.0f),
	                                         VECTOR3f(1.0f, 0.0f, 0.0f));
	Matrix4x4f_shearZ(&matrix, 0.5f, -0.5f);
	assertMatrixApproximate(matrix, 0.0f, 0.0f,  1.0f, 0.0f,
	                                1.0f, 0.0f,  0.5f, 0.0f,
	                                0.0f, 1.0f, -0.5f, 0.0f,
	                                0.0f, 0.0f,  0.0f, 1.0f, EPSILON);
}