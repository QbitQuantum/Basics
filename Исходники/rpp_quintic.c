int cubic(double A[4], double X[3], int* L)
{
	const double PI = 3.1415926535897932;
	const double THIRD = 1./3.;
	double U[3],W, P, Q, DIS, PHI;
	int i;

	//define cubic root as statement function
	// In C, the function is defined outside of the cubic fct

	// ====determine the degree of the polynomial ====

	if (A[3] != 0.0)
	{
		//cubic problem
		W = A[2]/A[3]*THIRD;
		P = pow((A[1]/A[3]*THIRD - (W*W)), 3);
		Q = -.5*(2.0*(W*W*W)-(A[1]*W-A[0])/A[3] );
		DIS = (Q*Q)+P;
		if ( DIS < 0.0 )
		{
			//three real solutions!
			//Confine the argument of ACOS to the interval [-1;1]!
			PHI = acos(min(1.0,max(-1.0,Q/sqrt(-P))));
			P=2.0*pow((-P),(5.e-1*THIRD));
			for (i=0;i<3;i++)	U[i] = P*cos((PHI+2*((double)i)*PI)*THIRD)-W;
			X[0] = min(U[0], min(U[1], U[2]));
			X[1] = max(min(U[0], U[1]),max( min(U[0], U[2]), min(U[1], U[2])));
			X[2] = max(U[0], max(U[1], U[2]));
			*L = 3;
		}
		else
		{
			// only one real solution!
			DIS = sqrt(DIS);
			X[0] = CBRT(Q+DIS)+CBRT(Q-DIS)-W;
			*L=1;
		}
	}
	else if (A[2] != 0.0)
	{
		// quadratic problem
		P = 0.5*A[1]/A[2];
		DIS = (P*P)-A[0]/A[2];
		if (DIS > 0.0)
		{
			// 2 real solutions
			const double sq_dis = sqrt(DIS);
			X[0] = -P - sq_dis;
			X[1] = -P + sq_dis;
			*L=2;
		}
		else
		{
			// no real solution
			*L=0;
		}
	}
	else if (A[1] != 0.0)
	{
		//linear equation
		X[0] =A[0]/A[1];
		*L=1;
	}
	else
	{
		//no equation
		*L=0;
	}
 //
 //     ==== perform one step of a newton iteration in order to minimize
 //          round-off errors ====
 //
	for (i=0;i<*L;i++)
	{
		X[i] = X[i] - (A[0]+X[i]*(A[1]+X[i]*(A[2]+X[i]*A[3])))/(A[1]+X[i]*(2.0*A[2]+X[i]*3.0*A[3]));
	//	printf("\n X inside cubic %.15e\n", X[i]);
	}

	return 0;
}