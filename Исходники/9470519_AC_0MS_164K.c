int main()
{
	scanf("%I64d%I64d",&n,&m);
	find_factor(m);
	ans=Pow(m,n);
	temp=1;
	for(i=1;i<=top;i++)
	{
		sum=0;
		find(1,0,i);
		temp*=-1;
		ans+=temp*sum;
	}
	printf("%I64d\n",ans);
	return 0;
}