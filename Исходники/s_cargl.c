DLLEXPORT long double
cargl(long double complex z)
{

	return (atan2l(cimagl(z), creall(z)));
}