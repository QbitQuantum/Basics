TEST( VectCrossCrossNorm, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	C = (A-B).cross(B);
	Vect D = C.cross(B);
	D.norm();

	CHECK( eq( D[x], 0.74790420f, MATH_TOLERANCE) );
	CHECK( eq( D[y], 0.04273730f, MATH_TOLERANCE) );
	CHECK( eq( D[z], -0.6624290f, MATH_TOLERANCE) );
	CHECK( D[w] == 1.0f );

	CHECK( C[x] == -9.0f );
	CHECK( C[y] == 18.0f );
	CHECK( C[z] == -9.0f );
	CHECK( C[w] == 1.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

}