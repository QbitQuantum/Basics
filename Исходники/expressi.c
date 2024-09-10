int main(void)
{
	double result, a = 3.31e-8, b = 2.01e-7, c = 7.16e-6, d = 2.01e-8;
	clrscr();
	result = (a*b)/(c+d);
	rintf("The expressin value is = %e", result);
	return 0;
}