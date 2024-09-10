int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);

	FB[1]=1;
	FB[2]=2;

	for(int i=3;i<=1002;++i)
		FB[i]=FB[i-1]+FB[i-2];

	kai[1]=0;
	kai[2]=0;
	kai[3]=1;
	
	for(int i=4;i<=1002;++i)
		kai[i]=kai[i-1]+FB[i-3];

	sum=0;
	for(int i=1;i<=1002;++i)
	{
		wei[i]=sum+1;
		sum=sum+FB[i];
	}

	int T;

	scanf("%d",&T);

	while(T--)
	{
		scanf("%*d");
		M.scan();
		getans();
	}

	return 0;
}