Verylong::Verylong(int n)
{
	int i;
	if ( n < 0 ) 
    { 
        vlsign = 1;
        n = (-n);
    }
	else 
        vlsign = 0;

	if ( n )
	{
		i = (int)log10((double)n)+2;
		vlstr = new char[i];
		vlen = i-1;
		i = 0;
		while (n >= 1)
		{
			vlstr[i] = n%10 + '0';
			n /= 10;
			i++;
		}
		vlstr[i] = '\0';
	}
	else
	{
        vlstr = NULL;
	    SetZero();
    }
}