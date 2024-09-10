void main()
{
	int a[100][100]={0},c,r,i,j=83,k=98,no,tot,ch,ro,co,gd=DETECT,gm,mx,my,x=60,y=75;
	char str[40];
	initgraph(&gd,&gm,"d:\\tc\\bgi");
	clrscr();
	printf("Enter size of  matrix");
	scanf("%d",&c);
	if(c%2==0)
	{
		printf("This is not defined for even numbers.");
		getch();
		exit();
	}
	printf("Enter initial value:");
	scanf("%d",&no);
	clrscr();
	setcolor(WHITE);
	fflush(stdin);
	settextstyle(3,HORIZ_DIR,10);
	setcolor(RED);
	itoa(c,str,10);
	settextstyle(0,HORIZ_DIR,1);
	j=(((c*42))/c)+43;
	mx=getmaxx();
	my=getmaxy();
	rectangle(0,0,mx,my);
	setcolor(RED);
	setfillstyle(SOLID_FILL,BLACK);
	floodfill(mx/2,my/2,BLACK);
	outtextxy(mx/2-150,40,"Magicsquare  of");
	outtextxy(mx/2,40,str);
	printf("\n\n\n");
	rectangle(45,60,(c+1)*42,(c+1)*42);
	setcolor(MAGENTA);
	setbkcolor(BLUE);
	setlinestyle(0,0,1);
	setcolor(MAGENTA);
	for(i=0;i<c-1;i++)
	{
		line(j,60,j,(c+1)*42);
		line(45,k,(c+1)*42,k);
		j+=(((c+1)*42)-45)/c;
		k+=(((c+1)*42)-60)/c;

	}
	c--;
	r=c;
	ro=r;
	co=ro;
	a[0][c/2]=no;
	ro=0;
	co=c/2;
	for(i=no+1;i<=((c+1)*(c+1))+no;i++)
	{
		ro--;
		co++;
		j=ro;
		k=co;
		if(ro<0 && co<=c)
			ro=c;
		if(ro<0 && co>c)
		{
			ro=c;
			co=0;
		}
		if(ro>=0 && co>c)
			co=0;
		if(a[ro][co]!=0)
		{
			ro=ro+2;
			co--;
		}
		if(ro==-1 && co==c+1  || j==-1 && k==c+1)
		{
			ro=1;
			co=c;
		}
	       a[ro][co]=i;
	}
	for(i=0;i<=c;i++)
	{
		x=60;
		for(j=0;j<=c;j++)
		{
		       //	printf("\t%d",a[i][j]);
			itoa(a[i][j],str,10);
			outtextxy(x,y,str);
			x+=40;
		}
		y+=40;
		printf("\n\n");
	}

		getch();
	closegraph();
	restorecrtmode();

}