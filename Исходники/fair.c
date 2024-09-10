int main()
{
	long long num,a,b,count,c=1,i,temp;
	scanf("%lld",&num);
	while(num--)
	{
		count=0;
		scanf("%lld%lld",&a,&b);
		for(i=a;i<=b;i++)
		{
			if(check(i))
			{
			temp=sqrtl(i);
			if(temp*temp==i)
				if(check(temp))
					count++;
			}
		}
		printf("Case #%lld: %lld\n",c++,count);
	}
	return 0 ;
}