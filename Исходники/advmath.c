//Taken from mathworld and wikipidia
long double dB(long double x)
{
long double ret;
if (fabsl(x)>1e-40)
{
	ret=(expl(x)-1.0-x*expl(x))/(expl(x)-1)/(expl(x)-1);
}
else
{
	ret= -1.0/2.0+x/6.0-powl(x,3.0)/180.0+powl(x,5.0)/5040;
}

return ret;
}