int main() {
	
	a = exp(a);
	b = expf(b);
	c = fastexp(c);
	d = fasterexp(c);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = log(a);
	b = logf(b);
	c = fastlog(c);
	d = fasterlog(c);
	printf("%f %f %f %f\n", a, b, c, d);	
	
	a = pow(a,a);
	b = pow(b,b);
	c = fastpow(c,c);
	d = fasterpow(c,c);
	printf("%f %f %f %f\n", a, b, c, d);			

	
	a = sin(a);
	b = sinf(b);
	c = fastsin(c);
	d = fastersin(c);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = cos(a);
	b = cosf(b);
	c = fastcos(c);
	d = fastercos(c);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = tan(a);
	b = tanf(b);
	c = fasttan(c);
	d = fastertan(c);
	printf("%f %f %f %f\n", a, b, c, d);	
	
	a = asin(a);
	b = asinf(b);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = acos(a);
	b = acosf(b);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = atan(a);
	b = atanf(b);
	printf("%f %f %f %f\n", a, b, c, d);	
	
	a = sinh(a);
	b = sinhf(b);
	c = fastsinh(c);
	d = fastersinh(c);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = cosh(a);
	b = coshf(b);
	c = fastcosh(c);
	d = fastercosh(c);
	printf("%f %f %f %f\n", a, b, c, d);
	
	a = tanh(a);
	b = tanhf(b);
	c = fasttanh(c);
	d = fastertanh(c);
	printf("%f %f %f %f\n", a, b, c, d);		
	
	a = lgamma(a);
	b = lgammaf(b);
	c = fastlgamma(c);
	d = fasterlgamma(c);
	printf("%f %f %f %f\n", a, b, c, d);		
	
	return 0;
	
}