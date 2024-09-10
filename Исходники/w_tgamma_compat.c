double
__tgamma(double x)
{
	int local_signgam;
	double y = __ieee754_gamma_r(x,&local_signgam);

	if(__glibc_unlikely (!isfinite (y) || y == 0)
	   && (isfinite (x) || (isinf (x) && x < 0.0))
	   && _LIB_VERSION != _IEEE_) {
	  if (x == 0.0)
	    return __kernel_standard(x,x,50); /* tgamma pole */
	  else if(__floor(x)==x&&x<0.0)
	    return __kernel_standard(x,x,41); /* tgamma domain */
	  else if (y == 0)
	    __set_errno (ERANGE); /* tgamma underflow */
	  else
	    return __kernel_standard(x,x,40); /* tgamma overflow */
	}
	return local_signgam < 0 ? -y : y;
}