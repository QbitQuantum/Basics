void
redlichKwong(	const CriticalParameters& inCP,

				double inT,			//	Temperature (K)
				double inP,			//	Pressure (bar)

				double* outZ,		//	Compressibility Factor
				//double* outState,
				double* outVol,		//	Molar volume (m^3/mol)
				double* outPhi,		//	Fugacity coefficient
				double* outHdep,	//	Enthalpy departure function
				double* outSdep)	//	Entropy departure function
{
	//	Calculate a and b parameters (depend only on critical parameters)…
	
	double a = 0.42748 * kR * kR * std::pow(inCP.mTc, 2.5) / (inCP.mPc * 1.0e5);
	double b = 0.08664 * kR * inCP.mTc / (inCP.mPc * 1.0e5);
	double kappa = 0.0;
	
	//	Calculate coefficients in the cubic equation of state…
	//
	//	coeffs: (C0,C1,C2,A,B);
	
	double A = a * inP * 1.0e5/ (std::sqrt(inT) * std::pow(kR * inT, 2));
	double B = b * inP * 1e5 / (kR * inT);
	double C2 = -1.0;
	double C1 = A - B - B * B;
	double C0 = -A * B;
	
	//	Solve the cubic equation for Z0 - Z2, D…
	
	double Z0;
	double Z1;
	double Z2;
	double D;
	solveCubic(C0, C1, C2, &Z0, &Z1, &Z2, &D);
	
	//	Determine the fugacity coefficient of first root and departure functions…
	//
	//	calcdepfns(coeffs[3],	coeffs[4],	paramsab[0],	Z[0]);
	//	calcdepfns(A,			B,			kappa,			Z)
	
	calcDepartureFunctions(inT, A, B, kappa, Z0, outPhi, outHdep, outSdep);
}