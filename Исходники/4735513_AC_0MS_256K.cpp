int main()
 {   
     int i,k,m;
	 double sum,total,temp;
     scanf("%lf %d",&total,&n);
	 for(i=1;i<=n;i++)
	 {
	   node[i].index=i;
	   scanf("%s",node[i].name);
	 }
	 qsort(node+1,n,sizeof(node[1]),cmp1);
	 scanf("%d",&m);
	 for(i=1;i<=m;i++)
	 {
		  scanf("%s %s %lf",name1,name2,&temp);
	      c[i].i=Bsearch(name1);
		  c[i].j=Bsearch(name2);
		  c[i].value=temp;
	 }	
	 qsort(c+1,m,sizeof(c[1]),cmp2); 
	 for(i=1;i<=n;i++)
			Makeset(i);
	 sum=0.0;k=1;
	 for(i=1;i<=m;i++)
	 {
		if(Find(c[i].i)!=Find(c[i].j))
		{
				sum=sum+c[i].value;
				Union(c[i].i,c[i].j);
				k++;
		}
		if(k==n)
				break;
	}
	if(total>=sum)
	    printf("Need %.1lf miles of cable\n",sum);
	else
	    printf("Not enough cable\n");
    return 0;
 }     