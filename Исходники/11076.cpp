int main()
{
	
	 
	while(1)
	{
		scanf("%ld",&n);
		if(n==0)
			break;
		add=count=0;
		for(i=0;i<n;i++)
		{
			scanf("%ld",&a[i]);
			add+=a[i];
			if(a[i]==0)
				count++;
		}
		if(count==n)
		{
			printf("0\n");
			continue;
		}
		pro=x[n-1];
		bool c[1000]={0};
		for(i=0;i<n;i++)
		{
			if(c[i]==0)
			{
				count=0;
			for(j=i+1;j<n;j++)
			{
				if(a[i]==a[j])
				{
					c[j]=1;
					count++;
				}
			}
			pro=pro/x[count];

			}
		}
		pro/=n;
		pro*=add;
		d=pro;
		for(i=0;i<n;i++)
		{
			b[i]=fmodl(pro,10);
			pro/=10;
			pro=floorl(pro);
			pro+=d;
		}
		if(d==0)
		{
			for(i=n-1;i>=0;i--)
			printf("%ld",a[i]);
		}
		else
		{
		if(pro>d)
		printf("%0.Lf",pro-d);
		for(i=n-1;i>=0;i--)
			printf("%ld",b[i]);
		}
		printf("\n");
	}
	return 0;
}