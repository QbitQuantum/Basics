unsigned propagaEntrada(void)
{
	int cont1,cont2;
	Y2temp=0;
	Y2=0;
	for (cont1=0;cont1<p;cont1++)
	{
		Y1temp[cont1]=0.0;
		for (cont2=0;cont2<n;cont2++)
			Y1temp[cont1]+=(W1[cont1][cont2]*entrada[cont2]);
		Y1[cont1]=tanhf(Y1temp[cont1]+b1[cont1]);
		Y2temp+=(W2[cont1]*Y1[cont1]);
	}
	Y2=tanhf(Y2temp+b2);
	return(OK);
}