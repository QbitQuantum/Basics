const bool Test_Matrix_ScalarMultiply()
{
	const TMatrix4d kA4d{	2.0, 0.0, 0.0, 0.0,
							0.0, 2.0, 0.0, 0.0,
							0.0, 0.0, 2.0, 0.0,
							0.0, 0.0, 0.0, 2.0};

	const TMatrix4f kA4f{	2.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 2.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 2.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 2.0f};


	const TMatrix3d kA3d{	2.0, 0.0, 0.0,
							0.0, 2.0, 0.0,
							0.0, 0.0, 2.0};

	const TMatrix3f kA3f{	2.0f, 0.0f, 0.0f,
							0.0f, 2.0f, 0.0f,
							0.0f, 0.0f, 2.0f};


	const TMatrix2d kA2d{	2.0, 0.0,
							0.0, 2.0};

	const TMatrix2f kA2f{	2.0f, 0.0f,
							0.0f, 2.0f};

	const bool kbPass4d = Equal(ScalarMultiply(TMatrix4d(), IdentityMatrix(TMatrix4d()), 2.0), kA4d, s_kdEpsilon);
	const bool kbPass4f = Equal(ScalarMultiply(TMatrix4f(), IdentityMatrix(TMatrix4f()), 2.0f), kA4f, s_kfEpsilon);
	const bool kbPass3d = Equal(ScalarMultiply(TMatrix3d(), IdentityMatrix(TMatrix3d()), 2.0), kA3d, s_kdEpsilon);
	const bool kbPass3f = Equal(ScalarMultiply(TMatrix3f(), IdentityMatrix(TMatrix3f()), 2.0f), kA3f, s_kfEpsilon);
	const bool kbPass2d = Equal(ScalarMultiply(TMatrix2d(), IdentityMatrix(TMatrix2d()), 2.0), kA2d, s_kdEpsilon);
	const bool kbPass2f = Equal(ScalarMultiply(TMatrix2f(), IdentityMatrix(TMatrix2f()), 2.0f), kA2f, s_kfEpsilon);

	return(		kbPass4d
			&&	kbPass4f
			&&	kbPass3d
			&&	kbPass3f
			&&	kbPass2d
			&&	kbPass2f);
}