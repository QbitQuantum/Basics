void
fun_C(int x, int y, int z)
{
	fesetround(FE_DOWNWARD);
	b=rintl(a);
	printf("%Lf\n", b);
}