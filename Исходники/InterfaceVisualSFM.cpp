inline TPoint2<TYPE> DistortPointR1(const TPoint2<TYPE>& pt, const REAL& k1) {
	if (k1 == 0)
		return pt;
	const REAL y(pt.y == 0 ? REAL(1.e-12) : REAL(pt.y));
	const REAL t2(y*y);
	const REAL t3(t2*t2*t2);
	const REAL t4(pt.x*pt.x);
	const REAL t7(k1*(t2+t4));
	const REAL t9(1.0/t7);
	const REAL t10(t2*t9*y*0.5);
	const REAL t11(t3*t9*t9*(0.25+t9/27.0));
	#ifndef _RELEASE
	TPoint2<TYPE> upt;
	#endif
	if (k1 > 0) {
		const REAL t17(CBRT(t10+SQRT(t11)));
		const REAL t18(t17-t2*t9/(t17*3));
		#ifndef _RELEASE
		upt =
		#else
		return
		#endif
			TPoint2<TYPE>(TYPE(t18*pt.x/y), TYPE(t18));
	} else {