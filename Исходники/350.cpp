int main()
{
	long double z,i,m,l,count,p,c,k;
	c=1;
	while(1)
	{
		scanf("%Lf %Lf %Lf %Lf",&z,&i,&m,&l);
		if(z==0&&i==0&&l==0&&m==0)
			break;
		count=0;
		while(1)
		{
		   p=(z*l)+i;
		   p=fmodl(p,m);
		   if(count==0)
			   k=p;
		   else if(p==k)
			   break;
		   count++;
		   l=p;
		}
		printf("Case %0.Lf: %0.Lf\n",c,count);
		c++;
	}
	return 0;
	}