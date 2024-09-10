	Int32 Quartic( Real x4, Real x3, Real x2, Real x, Real k, Real roots[4] )
	{
		if( IsZero( x4 ) )
			return Cubic( x3, x2, x, k, roots );
		
		Int32 n;
		Real a, b, c, d, s, a2, p, q, r, z, u, v;

		// Normalize
		a = x3 / x4;
		b = x2 / x4;
		c = x  / x4;
		d = k  / x4;

		// Reduction to a depressed quartic
		a2 = a * a;
		p = -3.0f / 8.0f * a2 + b;
		q = 1.0f / 8.0f * a2 * a - 1.0f / 2.0f * a * b + c;
		r = -3.0f / 256.0f * a2 * a2 + 1.0f / 16.0f * a2 * b - 1.0f / 4.0f * a * c + d;

		if( IsZero( r ) )
		{
			n = Cubic( 1.0f, 0.0f, p, q, roots );
			roots[n++] = 0.0f;
		}
		else
		{
			Cubic( 1.0f, -1.0f / 2.0f * p, -r, 1.0f / 2.0f * r * p - 1.0f / 8.0f * q * q, roots );

			z = roots[0];
			u = z * z - r;
			v = 2.0f * z - p;

			if( u < -CLOSE ) return 0;
			else u = u > CLOSE ? SQRT( u ) : 0.0f;

			if( v < -CLOSE ) return 0;
			else v = v > CLOSE ? SQRT( v ) : 0.0f;

			n  = Quadratic( 1.0f, q < 0.0f ? -v : v, z - u, roots );
			n += Quadratic( 1.0f, q < 0.0f ? v : -v, z + u, roots + n );
		}

		s = 1.0f / 4.0f * a;
		for( Int32 i = 0; i < n; i++ )
			roots[i] -= s;

		return n;
	}