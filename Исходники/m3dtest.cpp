void m3dTest::orthonormalInverseTest()
{
	using namespace m3d;
	Vec3f dir(frand(), frand(), frand());
	Vec3f pos(frand(), frand(), frand());
	Mat4f matrix = Mat4f::gramSchmidt(dir, pos);

	Mat4f inverse = matrix.inverse();
	Mat4f orth_inverse = matrix.orthonormalInverse();

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			// check if equal
			CPPUNIT_ASSERT(fabs(inverse[x][y] - orth_inverse[x][y]) < EPSILON);

			// check for NaN
			CPPUNIT_ASSERT(inverse[x][y] == inverse[x][y]);
			CPPUNIT_ASSERT(orth_inverse[x][y] == orth_inverse[x][y]);
		}
	}
}