	void Matrix2Test::testConstantFunctionDeterminant(){
		const Matrix2f matrix( 1.0f, 2.0f, 3.0f, 4.0f );
		
		const float result = matrix.Determinant();
		const float expected = -2;
		
		CPPUNIT_ASSERT_EQUAL( expected, result );
	}