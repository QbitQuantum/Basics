int main ()
{
	long long int k , a, b;
	
	long long int i;
	
	scanf("%lld %lld %lld", &k, &a, &b);
	long long int count = 0;
	
	
	long long int t1, t2,z1, z2, ans;
	

	if (a == 0 || b==0 )
	{
		if (a == 0)
		{
			t2 = llabs(b - (b%k));
			z2 = t2/k;
			count = z2 +1;
		}
		else
		{
			t1 = llabs(a - (a%k));
			z1 = t1/k;
			count = z1+1;
		}
	}

	else if ( (a >= 0 && b >= 0) || (a<0 && b<0))
	{

		if ((a<0 && b <0) && (b%k)==0)
			count++;
		else if ((a>0 && b>0) && (a%k)==0)
			count++;

		t2 = llabs( b - (b%k));
		t1 = llabs(a - (a%k));
		
		z1 = t1/k;
		z2 = t2/k;
	
		if ( a<0 && b <0)
		count = count + (z1-z2);
		else
			count = count + (z2-z1);
	}

	else if (( a> 0 && b<0) || (a<0 && b>0))
	{
		t2 = llabs( b - (b%k) );
		t1 = llabs (a - (a%k));

		z1 = t1/k;
		z2 = t2/k;

		count = count + (z2+z1) + 1;
	}
	printf("%lld\n", count);

	return 0;
}