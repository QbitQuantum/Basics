Err mathlib_rint(UInt16 refnum, double x, double *result) {
#pragma unused(refnum)
	*result = __rint(x);
	return mlErrNone;
}