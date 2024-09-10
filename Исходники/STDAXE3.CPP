void axele(double *d)
{
int c;
double zero[3];
void limite(double *d,double *e);
void drawaxe(double *f);
	puts("Did you want axes ? (y/n)");
	flushall();
	c=bioskey(0);
	if(c==5465||c==5497)
	{
		limite(d,zero);
		drawaxe(zero);
	}
	else
		cleardevice();
	return;
}