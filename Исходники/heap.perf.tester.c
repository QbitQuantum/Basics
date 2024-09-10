int main()
{
	int i,n,x;
	heap *p=NULL;
	p=heapAlloc();
	scanf("%d",&n);
	heapInit(p,sizeof(int),n+1,gt);
	for(i=0;i<n/2;i++)
	{
		x=i+n/2;
		heapPush(p,&x);
	}
	for(i=0;i<n/2;i++)
		heapPush(p,&i);
	while(!heapEmpty(p))
	{
		heapPop(p,&x);
		printf("%d%c",x,heapEmpty(p)?'\n':' ');
	}
	return 0;
}