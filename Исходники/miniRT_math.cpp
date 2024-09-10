	// ----------------------------------------------------------
	//  Name:   matrix::Determinant
	//  Desc:   Return the matrix determinant. A = det[M].
	// ----------------------------------------------------------
	float matrix::Determinant() {
#ifdef _M_IX86
		__m128 Va,Vb,Vc;
		__m128 r1,r2,r3,t1,t2,sum;
		F32vec4 Det;

		// First, Let's calculate the first four minterms of
		// the first line
		t1 = _L4; t2 = _mm_ror_ps(_L3,1); 
		// V3'·V4
		Vc = _mm_mul_ps(t2,_mm_ror_ps(t1,0));
		// V3'·V4"
		Va = _mm_mul_ps(t2,_mm_ror_ps(t1,2));
		// V3'·V4^
		Vb = _mm_mul_ps(t2,_mm_ror_ps(t1,3));

		// V3"·V4^ - V3^·V4"
		r1 = _mm_sub_ps(_mm_ror_ps(Va,1),_mm_ror_ps(Vc,2));
		// V3^·V4' - V3'·V4^
		r2 = _mm_sub_ps(_mm_ror_ps(Vb,2),_mm_ror_ps(Vb,0));
		// V3'·V4" - V3"·V4'
		r3 = _mm_sub_ps(_mm_ror_ps(Va,0),_mm_ror_ps(Vc,1));

		Va = _mm_ror_ps(_L2,1);
		sum = _mm_mul_ps(Va,r1);
		Vb = _mm_ror_ps(Va,1);
		sum = _mm_add_ps(sum,_mm_mul_ps(Vb,r2));
		Vc = _mm_ror_ps(Vb,1);
		sum = _mm_add_ps(sum,_mm_mul_ps(Vc,r3));

		// Now we can calculate the determinant:
		Det = _mm_mul_ps(sum,_L1);
		Det = _mm_add_ps(Det,_mm_movehl_ps(Det,Det));
		Det = _mm_sub_ss(Det,_mm_shuffle_ps(Det,Det,1));
		return Det[0];
#else
		// TODO
		return 0.0f;
#endif // _M_IX86
	}