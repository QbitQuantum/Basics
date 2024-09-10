int main()
{
	static long long int ch[7][100005],ce[7][100005],cf[7][100005],hf[7][100005],ef[7][100005],he[7][100005],l,r,i,j,n,res,p1,p2,whole,aapas,door,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
	char ar[1000006],a,b;
	scanf("%s",ar);
	scanf("%lld",&n);
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='c')
		{
			//ch
			ch[1][j]=ch[1][j-1]+1;
			ch[2][j]=ch[2][j-1]+0;
			p1=p1-ch[2][j];
			ch[3][j]=p1;
			ch[5][j]=ch[5][j-1]+1;
			ch[4][j]=ch[4][j-1]+0;
			ch[6][j]=p2;
			//ce
			
			//cf
			
			
			
			j++;
			
		}
	
		else if(ar[i]=='h')
		{
			//hc
			ch[2][j]=ch[2][j-1]+1;
			ch[1][j]=ch[1][j-1]+0;
			
			ch[3][j]=ch[3][j-1]+0;
			ch[4][j]=ch[4][j-1]+1;
			ch[5][j]=ch[5][j-1]+0;
			p2=p2-ch[5][j];
			ch[6][j]=p2;
			//hf
			
			//he
			
			
		
			j++;
		}

	}
	//ce
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='c')
		{
			ce[1][j]=ce[1][j-1]+1;
			ce[2][j]=ce[2][j-1]+0;
			p3=p3-ce[2][j];
			ce[3][j]=p3;
			ce[5][j]=ce[5][j-1]+1;
			ce[4][j]=ce[4][j-1]+0;
			ce[6][j]=p4;
			j++;
		}
		else if(ar[i]=='e')
		{
			ce[2][j]=ce[2][j-1]+1;
			ce[1][j]=ce[1][j-1]+0;
			
			ce[3][j]=ce[3][j-1]+0;
			ce[4][j]=ce[4][j-1]+1;
			ce[5][j]=ce[5][j-1]+0;
			p4=p4-ce[5][j];
			ce[6][j]=p4;
			j++;
		}
	}
//hf
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='h')
		{
			hf[1][j]=hf[1][j-1]+1;
			hf[2][j]=hf[2][j-1]+0;
			p5=p5-hf[2][j];
			hf[3][j]=p5;
			hf[5][j]=hf[5][j-1]+1;
			hf[4][j]=hf[4][j-1]+0;
			hf[6][j]=p6;
			j++;
		}
		else if(ar[i]=='f')
		{
			hf[2][j]=hf[2][j-1]+1;
			hf[1][j]=hf[1][j-1]+0;
			
			hf[3][j]=hf[3][j-1]+0;
			hf[4][j]=hf[4][j-1]+1;
			hf[5][j]=hf[5][j-1]+0;
			p6=p6-hf[5][j];
			hf[6][j]=p6;
			j++;
		}
	}
	//ef
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='e')
		{
			ef[1][j]=ef[1][j-1]+1;
			ef[2][j]=ef[2][j-1]+0;
			p7=p7-ef[2][j];
			ef[3][j]=p7;
			ef[5][j]=ef[5][j-1]+1;
			ef[4][j]=ef[4][j-1]+0;
			ef[6][j]=p8;
			j++;
		}
		else if(ar[i]=='f')
		{
			ef[2][j]=ef[2][j-1]+1;
			ef[1][j]=ef[1][j-1]+0;
			
			ef[3][j]=ef[3][j-1]+0;
			ef[4][j]=ef[4][j-1]+1;
			ef[5][j]=ef[5][j-1]+0;
			p8=p8-ef[5][j];
			ef[6][j]=p8;
			j++;
		}
	}
	//he
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='h')
		{
			he[1][j]=he[1][j-1]+1;
			he[2][j]=he[2][j-1]+0;
			p9=p9-he[2][j];
			he[3][j]=p9;
			he[5][j]=he[5][j-1]+1;
			he[4][j]=he[4][j-1]+0;
			he[6][j]=p10;
			j++;
		}
		else if(ar[i]=='e')
		{
			he[2][j]=he[2][j-1]+1;
			he[1][j]=he[1][j-1]+0;
			
			he[3][j]=he[3][j-1]+0;
			he[4][j]=he[4][j-1]+1;
			he[5][j]=he[5][j-1]+0;
			p10=p10-he[5][j];
			he[6][j]=p10;
			j++;
		}
	}
	//cf
	for(i=0,j=1;ar[i]!='\0';i++)
	{
		if(ar[i]=='c')
		{
			cf[1][j]=cf[1][j-1]+1;
			cf[2][j]=cf[2][j-1]+0;
			p11=p11-cf[2][j];
			cf[3][j]=p11;
			cf[5][j]=cf[5][j-1]+1;
			cf[4][j]=cf[4][j-1]+0;
			cf[6][j]=p12;
			j++;
		}
		else if(ar[i]=='f')
		{
			cf[2][j]=cf[2][j-1]+1;
			cf[1][j]=cf[1][j-1]+0;
			cf[3][j]=cf[3][j-1]+0;
			cf[4][j]=cf[4][j-1]+1;
			cf[5][j]=cf[5][j-1]+0;
			p12=p12-cf[5][j];
			cf[6][j]=p12;
			j++;
		}
	}
	for(i=1;i<=6;i++)
	{
		for(j=1;j<=10;j++)
		{
			printf("%lld ",ce[i][j]);
		}printf("\n");
	}

	while(n--)
	{
		scanf("\n%c\n%c\n%lld%lld",&a,&b,&l,&r);
			
		if(a=='c'&&b=='h')
		{
			whole=ch[1][r]*ch[2][r]+ch[3][r];
			aapas=ch[1][l-1]*ch[2][l-1]+ch[3][l-1];
			door=ch[1][l-1]*(ch[2][r]-ch[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='h'&&b=='c')
		{
			whole=ch[4][r]*ch[5][r]+ch[6][r];
			aapas=ch[4][l-1]*ch[5][l-1]+ch[6][l-1];
			door=ch[4][l-1]*(ch[5][r]-ch[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='c'&&b=='e')
		{
			whole=ce[1][r]*ce[2][r]+ce[3][r];
			aapas=ce[1][l-1]*ce[2][l-1]+ce[3][l-1];
			door=ce[1][l-1]*(ce[2][r]-ce[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='e'&&b=='c')
		{
			whole=ce[4][r]*ce[5][r]+ce[6][r];
			aapas=ce[4][l-1]*ce[5][l-1]+ce[6][l-1];
			door=ce[4][l-1]*(ce[5][r]-ce[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='h'&&b=='f')
		{
			whole=hf[1][r]*hf[2][r]+hf[3][r];
			aapas=hf[1][l-1]*hf[2][l-1]+hf[3][l-1];
			door=hf[1][l-1]*(hf[2][r]-hf[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='f'&&b=='h')
		{
			

            whole=hf[4][r]*hf[5][r]+hf[6][r];
			aapas=hf[4][l-1]*hf[5][l-1]+hf[6][l-1];
			door=hf[4][l-1]*(hf[5][r]-hf[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='e'&&b=='f')
		{
			whole=ef[1][r]*ef[2][r]+ef[3][r];
			aapas=ef[1][l-1]*ef[2][l-1]+ef[3][l-1];
			door=ef[1][l-1]*(ef[2][r]-ef[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='f'&&b=='e')
		{
			whole=ef[4][r]*ef[5][r]+ef[6][r];
			aapas=ef[4][l-1]*ef[5][l-1]+ef[6][l-1];
			door=ef[4][l-1]*(ef[5][r]-ef[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='h'&&b=='e')
		{
			whole=he[1][r]*he[2][r]+he[3][r];
			aapas=he[1][l-1]*he[2][l-1]+he[3][l-1];
			door=he[1][l-1]*(he[2][r]-he[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='e'&&b=='h')
		{
			
			whole=he[4][r]*he[5][r]+he[6][r];
			aapas=he[4][l-1]*he[5][l-1]+he[6][l-1];
			door=he[4][l-1]*(he[5][r]-he[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}
		else if(a=='c'&&b=='f')
		{
			whole=cf[1][r]*cf[2][r]+cf[3][r];
			aapas=cf[1][l-1]*cf[2][l-1]+cf[3][l-1];
			door=cf[1][l-1]*(cf[2][r]-cf[2][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);

		}
		else if(a=='f'&&b=='c')
		{
			whole=cf[4][r]*cf[5][r]+cf[6][r];
			aapas=cf[4][l-1]*cf[5][l-1]+cf[6][l-1];
			door=cf[4][l-1]*(cf[5][r]-cf[5][l-1]);
			res=whole-(aapas+door);
			printf("%lld\n",res);
		}

		
	}
	return 0;
}