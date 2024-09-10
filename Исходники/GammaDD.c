static long double GammaCommon( double dhead, double dtail, int igamma )
{
	int signgam, ireflect, increase, i;
	
	double int1, int2, arg, arg2, arg3, argt, arg2t, anew;
	double factor, factor1, factor2, factor3, f1, f2, f3;
	double prod1, prod2, pextra, pextra1, pextra2, sum1, sum2, sextra;
	double sum21, sum22, sextra2, sum31, sum32, sextra3;
	double diff1, diff2, dextra, sarg1, sarg2, saextra;
	double denom1, denom2, sum, suml, sumt, recip1, recip2, recipsq1, recipsq2;
	double extra, extra2, extra3, extrax, extray, extralg, gmextra;
	double temp, eexp, diff, z, z2, y, y2, y3, asize, c;
	
	DblDbl gamdd, tempdd, intdd, xhintdd, sinargdd;
	
	DD *bern = (DD *)(bernData - 4);
	DD *zeta = (DD *)(zetaData - 8);

	signgam = 1;

	if (dhead <= 0) {					// special for neg arguments
		tempdd.d[0] = dhead;
		tempdd.d[1] = dtail;
		intdd.f = rintl(tempdd.f);		// get integer part of argument
		int1 = intdd.d[0];
		int2 = intdd.d[1];
		
		if (isinf(dhead) || (dhead - int1 + dtail - int2) == 0) {
			
			//*********************************************************************
			//    Argument is a non-positive integer.  Gamma is not defined.      *
			//    Return a NaN. 		                                          *
			//*********************************************************************
			gamdd.d[0] = INFINITY; // per IEC, [was: zero/zero;]
			gamdd.d[1] = zero;
			return gamdd.f;
		}
		if (dhead > -20.0) {
			ireflect = 0;				// reflection formula not used for
										// modest sized neg numbers
		}
		else {
			ireflect = 1;				// signal use of reflection formula
			dhead = -dhead;				// change sign of argument
			dtail = -dtail;
		}
	}
	else								// else, positive arguments --
		ireflect = 0;					// signal reflection formula not used
	
	if (isinf(dhead) || (dhead + dtail) != (dhead + dtail)) {
		gamdd.d[0] = dhead + dtail;
		gamdd.d[1] = zero;
		return gamdd.f;
	}
	
	arg  = dhead;						// working copy of argument
	arg2 = dtail;
	arg3 = 0.0;
	factor1 = 1.0;
	factor2 = 0.0;
	factor3 = 0.0;
	
	if (arg > 18.0) {					// use asymptotic formula
		while (arg < 31.0) {
			_d3mul( factor1, factor2, factor3, arg, arg2, arg3,
						&factor1, &factor2, &factor3 );
			arg = arg + 1.0;
		}								// argument in range for asympt. formula
		while (arg < 35.0) {
			_d3mul( factor1, factor2, factor3, arg, arg2, arg3,
						&factor1, &factor2, &factor3 );
			argt = __FADD( arg, 1.0 );
			arg2t = __FADD( (arg - argt + 1.0), arg2 );
			arg3 = ((arg - argt + 1.0) - arg2t + arg2) + arg3;
			arg = argt;
			arg2 = arg2t;
		}
		tempdd.f = _LogInnerLD(arg, arg2, 0.0, &f3, 1);		// ln x
		f3 = f3 + arg3/arg;
		f1 = tempdd.d[0];
		f2 = tempdd.d[1];

		_d3mul(f1, f2, f3, (arg - 0.5), arg2, arg3,
					&prod1, &prod2, &c);					// (x-.5)ln x
		_d3add(prod1, prod2, c, -arg, -arg2, -arg3,
					&sum1, &sum2, &sextra);					// (x-.5)ln x-x
		_d3add(sum1, sum2, sextra, bump.f, bump2.f, bump3.f,
					&sum21, &sum22, &sextra2);
		
		//**************************************************************
		//   sum21, sum22, sextra2 represent (x-.5)ln x-x+.5 ln(2 Pi)  *
		//**************************************************************
		
		_d3div(1.0, 0.0, 0.0, arg, arg2, arg3, &recip1, &recip2, &extra);
		
		// argument for asymptotic formula
		_d3mul(recip1, recip2, extra, recip1, recip2, extra,
					&recipsq1, &recipsq2, &extra2);
		
		sum  = bern[11][0];
		suml = bern[11][1];
		for (i = 10; i >= 1; --i) {
			temp = __FMADD( sum, recipsq1, bern[i][0] ); // bern[i][0] + sum*recipsq1;
			/* suml = bern[i][0] - temp + sum*recipsq1 +
			         (bern[i][1] + sum*recipsq2 + suml*recipsq1); */
			suml = __FMADD( sum, recipsq1, bern[i][0] - temp ) +
					__FMADD( suml, recipsq1, __FMADD( sum, recipsq2, bern[i][1] ) );
			sum = temp;
		}								// finish summation of asymptotic series

		_d3mul(sum, suml, 0.0, recip1, recip2, extra, &prod1, &prod2, &extra3);
		_d3add(sum21, sum22, sextra2, prod1, prod2, extra3, &sum31, &sum32, &sextra3);
		
		//******************************************************************************
		//   At this point, log(gamma*factor) is computed as (sum31, sum32, sextra3).  *
		//******************************************************************************
		
		if ((igamma == 1) && (ireflect != 1))  {
			// Gamma entry point (without use of reflection formula)?
			tempdd.f = _ExpInnerLD(sum31, sum32, sextra3, &eexp, 4);
			if (factor1 == 1.0) {
				gamdd.f = tempdd.f;
				gmextra = eexp;
			}
			else {
				_d3div(tempdd.d[0], tempdd.d[1], eexp, factor1, factor2, factor3,
							&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
			}
		}
		else {							// Computing log(gamma(x))
			factor = factor1;
			if (factor == 1.0) {
				gamdd.d[0] = sum31;
				gamdd.d[1] = sum32;
				gmextra = sextra3;
			}
			else {
				tempdd.f = _LogInnerLD(factor1, factor2, 0.0, &extrax, 1);
				// computing log gamma.
				extray = -(extrax + factor3/factor);
				_d3add(sum31, sum32, sextra3, -tempdd.d[0], -tempdd.d[1], extray,
							&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
			}
		}
	}
	else {								// use formula for interval [0.5,1.5]
		arg = dhead;
		arg2 = dtail;					// working copy of argument
		arg3 = 0.0;
		increase = 0;					// signal-> no scaling for result
		if (arg < 1.5) {				// scale up argument by recursion formula
			increase = -1;				// signal-> result to be divided by factor
			factor1 = arg;
			factor2 = arg2;
			factor3 = 0.0;				// factor is the old argument
			while (arg < 1.5) {
				_d3add(arg, arg2, arg3, 1.0, 0.0, 0.0, &arg, &arg2, &arg3);
				if (arg < 1.5) {
					_d3mul(factor1, factor2, factor3, arg, arg2, arg3,
								&factor1, &factor2, &factor3);
				}
			}
			if (factor1 < 0.0) {
				signgam = -1;			// special case of negative arguments
			}
		}
		else if (arg > 2.5) {
			increase = +1;				// signal-> result must be mult by factor
			factor1 = 1.0;
			factor2 = 0.0;
			factor3 = 0.0;
			while (arg > 2.5) {						// reduce argument by 1
				arg = arg - 1.0;					// there may be room for bits to
				anew = __FADD( arg, arg2 );			// shift from low order word to
				arg2 = arg - anew + arg2;			// high order word
				arg = anew;
				_d3mul(factor1, factor2, factor3, arg, arg2, 0.0,
								&factor1, &factor2, &factor3);
			}
			arg3 = 0.0;
		}
		diff = __FSUB( arg, 2.0 );					// series in terms of
		z = __FADD( (arg - (diff + 2.0)), arg2 );	// (diff,z,x2)=arg-2
		z2 = (arg - (diff + 2.0)) - z + arg2 + arg3;
		y = __FADD( diff, z );
		y2 = (diff - y + z) + z2;
		y3 = (diff - y + z) - y2 + z2;
		sum  = zeta[53][0];
		suml = zeta[53][1];
		for (i = 52; i >= 40; --i) {
			sum = __FMADD( sum, y, zeta[i][0] ); // zeta[i][0] + sum*y;
		}
		sumt = __FMADD( sum, y, zeta[39][0] ); // zeta[39][0] + sum*y;
		suml = __FMADD( sum, y, zeta[39][0] - sumt) + __FMADD( sum, y2, zeta[39][1] ); // zeta[39][0] - sumt + sum*y + (zeta[39][1] + sum*y2);
		sum = sumt;
		for (i = 38; i >= 3; --i) {
			temp = __FMADD( sum, y, zeta[i][0] ); // zeta[i][0] + sum*y;
			// suml = (zeta[i][0] - temp + sum*y) + zeta[i][1] + (sum*y2 + suml*y);
			suml = __FMADD( sum, y, zeta[i][0] - temp ) +  zeta[i][1] + __FMADD( sum, y2, suml*y ); 
			sum = temp;
		}
		_d3mul(sum, suml, 0.0, y, y2, y3, &prod1, &prod2, &pextra2);
		_d3add(prod1, prod2, pextra2, zeta[2][0], zeta[2][1], zeta32.f,
					&sum1, &sum2, &sextra);
		_d3mul(sum1, sum2, sextra, y, y2, y3,
					&prod1, &prod2, &pextra1);  			// multiply sum by z
		_d3add(prod1, prod2, pextra1, ec.f, ec2.f, ec3.f,
					&sum1, &sum2, &sextra);	 				// add linear term
		_d3mul(sum1, sum2, sextra, y, y2, y3,
					&prod1, &prod2, &pextra);				// final mult. by z.
		
		if (igamma == 1) {			 // a Gamma entry
			tempdd.f = _ExpInnerLD(prod1, prod2, pextra, &eexp, 4);
			if (increase == 1) {
				_d3mul(tempdd.d[0], tempdd.d[1], eexp, factor1, factor2, factor3,
								&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
			}
			else if (increase == -1) {
				_d3div(tempdd.d[0], tempdd.d[1], eexp, factor1, factor2, factor3,
								&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
			}
			else {
				gamdd.f = tempdd.f;
				gmextra = eexp;
			}
		}
		else {				// entry was for log gamma
			if (increase == 0) {
				gamdd.d[0] = prod1;
				gamdd.d[1] = prod2;
				gmextra = pextra;
			}
			else {
				if (signgam < 0) {
					factor1 = -factor1;
					factor2 = -factor2;
					factor3 = -factor3;
				}
				factor = factor1;
				tempdd.f = _LogInnerLD(factor1, factor2, 0.0, &extra, 1);
				extra = extra + factor3/factor;
				if (increase == -1) {				// change sign of log
					tempdd.d[0] = -tempdd.d[0];
					tempdd.d[1] = -tempdd.d[1];
					extra = -extra;
				}
				_d3add(prod1, prod2, pextra, tempdd.d[0], tempdd.d[1], extra,
							&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
			}
		}
	}
	
	if (gamdd.d[0] != gamdd.d[0]) {
		gamdd.d[0] = infinity.f;
		gamdd.d[1] = zero;
		gmextra = 0.0;
	}
	
	if (ireflect == 1) {							// original argument less than 0.0
		arg = -dhead;								// recover original argument
		arg2 = -dtail;
													// reduce argument for computation
		_d3add(arg, arg2, 0.0, -int1, -int2, 0.0, &diff1, &diff2, &dextra);
		asize = fabs(diff1);

		if (asize < tiny.f) {  				 		// For arguments very close
			diff1  *= scaleup.f;					// to an integer, rescale,
			diff2  *= scaleup.f;            		// so that sin can be computed
			dextra *= scaleup.f;					// to a full 107+ bits
		}											// of sin (Pi x)

		_d3mul(diff1, diff2, dextra, pi.f, pib.f, pic.f, &sarg1, &sarg2, &saextra);
		xhintdd.f = 2.0*rintl(0.5*intdd.f);
		
		tempdd.d[0] = sarg1;
		tempdd.d[1] = sarg2;
		sinargdd.f = sinl(tempdd.f);				// sin of argument

		if ((xhintdd.d[0] - intdd.d[0] + xhintdd.d[1] - intdd.d[1]) != 0.0) {
			sinargdd.f = -sinargdd.f;
		}
			
		if (sinargdd.d[0] < 0.0) {
			sinargdd.f = -sinargdd.f;				// force sin(pi x) to have plus sign
			signgam = -signgam;						// show gamma(x) has negative sign
		}

		if (fabs(gamdd.d[0]) == infinity.f){		// result will underflow
			if(igamma == 1) {
				gamdd.d[0] = zero;
				gamdd.d[1] = zero;
			}
			else {
				gamdd.d[0] = -infinity.f;			//  gamma underflows, so
				gamdd.d[1] = zero;					//  lgamma overflows to -INF
			}
			return gamdd.f;
		}
		_d3mul(dhead, dtail, 0.0, sinargdd.d[0], sinargdd.d[1], 0.0,
					&prod1, &prod2, &pextra);		//  x sin(pi x)
		
		tempdd.f = _LogInnerLD(prod1, prod2, 0.0, &extralg, 1);	// log (x sin(pi x))
		extralg = extralg + pextra/prod1;
		_d3add(tempdd.d[0], tempdd.d[1], extralg, gamdd.d[0], gamdd.d[1], gmextra,
					&denom1, &denom2, &dextra);
		_d3add(piln.f, pilnb.f, pilnc.f, -denom1, -denom2, -dextra,
					&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
		
		if (asize < tiny.f) {
			// Compensate for scaling of argument to sin(pi x)
			_d3add(gamdd.d[0], gamdd.d[1], gmextra, sclog.f, sclog2.f, sclog3.f,
						&(gamdd.d[0]), &(gamdd.d[1]), &gmextra);
		}
		if (igamma == 1) {    // we really want gamma itself ?
			tempdd.f = _ExpInnerLD(gamdd.d[0], gamdd.d[1], gmextra, &eexp, 4);
			
			if (signgam == 1) {
				gamdd.f = tempdd.f;
			}
			else {
				gamdd.f = -tempdd.f;
			}
		}
	}
	return gamdd.f;
}	