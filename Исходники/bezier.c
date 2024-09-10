void main()
{
	int gd=DETECT,gm;
	int i,n,x[4],y[4],x1,y1;
	float u;
	printf("Enter no of controlling points(4): ");
	scanf("%d",&n);
	printf("Enter the coordinates\n");
	for(i=0;i<4;i++)
	{
		printf("Point %d(x,y):\n",i+1);
		scanf("%d%d",&x[i],&y[i]);
	}
	initgraph(&gd,&gm,"");
	for(i=0;i<3;i++)
		line(x[i],y[i],x[i+1],y[i+1]);
	moveto(x[0],y[0]);	 	
	for(u=0;u<1;u=u+0.0001)
	{
		delay(5);	
		x1=pow(1-u,3)*x[0]+3*u*pow(1-u,2)*x[1]+3*u*u*(1-u)*x[2]+u*u*u*x[3];
		y1=pow(1-u,3)*y[0]+3*u*pow(1-u,2)*y[1]+3*u*u*(1-u)*y[2]+u*u*u*y[3];
		setcolor(5); 
		lineto(x1,y1);		
	}
	getch();
}