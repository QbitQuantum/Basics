HugeNumber operator % ( HugeNumber &u, HugeNumber &v)
// Ostatok ot delenija
{
	HugeNumber a,r;
	Div(u,v,a,r);
	return r;
};