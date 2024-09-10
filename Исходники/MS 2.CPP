void main()
{       char c,ch,ch1;
	FILE *ssa;
	int gdriver=DETECT,gmode,errorcode,x,y;
	initgraph(&gdriver,&gmode,"c:\\turboc3\\bgi");
	setbkcolor(18);
	for(int k=0;k<25;k++)
	{       setcolor(3);
		delay(40);
		ellipse(320,240,0,360,200+k,50);
	}
	settextstyle(GOTHIC_FONT,0,5);
	outtextxy(170,210,"MINESWEEPER");
	getch();
	setcolor(15);
  print:clearviewport();
	settextstyle(TRIPLEX_FONT,0,2);
	setcolor(3);
	rectangle(80,130,570,240);
	rectangle(85,135,565,235);
	outtextxy(100,140,"  BEGINNER   LEVEL1: 9X9   GRID 10 MINES");
	outtextxy(100,170,"INTERMEDIATE LEVEL2:10X10 GRID 16 MINES");
	outtextxy(100,200,"  ADVANCED   LEVEL3:13X13 GRID 30 MINES");
	settextstyle(DEFAULT_FONT,0,1);
	outtextxy(250,250,"ENTER THE LEVEL:");
	outtextxy(100,380,"PRESS ESCAPE TO QUIT");
	outtextxy(100,410,"PRESS F1 FOR HELP");
	outtextxy(100,440,"PRESS F2 FOR CONTROLS");
	c=getche();
	clearviewport();
	if     (c=='1') {       x=minx=140;y=miny=120;mines=flag1=10;grid=9;	}
	else if(c=='2')	{	x=minx=120;y=miny=110;flag1=mines=16;grid=10;	}
	else if(c=='3') {	x=minx=60;y=miny=70;mines=flag1=30;grid=13;	}
	else if(c==27)	        exit(1);
	else if(c==';'||c=='<')
	{	clearviewport();
		if(c==';')
			ssa=fopen("c:\\turboc3\\sp.txt","r");
		if(c=='<')
			ssa=fopen("c:\\turboc3\\sp1.txt","r");
		while((ch1=fgetc(ssa))!= EOF)
		      printf("%c",ch1);
		printf("\nPRESS ANY KEY TO EXIT");
		getch();
		rewind(ssa);
		goto print;
	}
	else 	goto print;
	maxx=minx+(grid-1)*40;
	maxy=miny+(grid-1)*30;
	setbkcolor(15);
	setcolor(8);//box colour
	for(int i=0;i<grid;i++)
		for(int j=0;j<grid;j++)
		{	rectangle(minx+i*40,miny+j*30,minx+(i+1)*40,miny+(j+1)*30);
			setfillstyle(SOLID_FILL,15);
			bar(minx+5+i*40,miny+5+j*30,minx+35+i*40,miny+25+j*30);
			rectangle(minx+5+i*40,miny+5+j*30,minx+35+i*40,miny+25+j*30);
		}
		settextstyle(TRIPLEX_FONT,0,5);
		setcolor(3);
		outtextxy(190,10,"MINESWEEPER");
		settextstyle(DEFAULT_FONT,0,1);
	minegen();
	do
	{       ch=getche();
		setcolor(8);	//resets box colorto frame color
		if(ch=='f'||ch=='F')
		{	setcolor(1);	flag(x,y);	}
		if(ch=='s'||ch=='S')
		{	setcolor(4);	open(x,y);	}
		if(ch==27)
			exit(1);
		if((x==minx&&ch==75)||(y==maxy&&ch==80)||(x==maxx&&ch==77)||(y==miny&&ch==72))
				setcolor(4);
		else    rectangle(x+5,y+5,x+35,y+25);
		switch(ch)
		{ 	case 72:if(y>miny)
				y=y-30;
				break;
			case 80:if(y<maxy)
				y=y+30;
				break;
			case 75:if(x>minx)
				x=x-40;
				break;
			case 77:if(x<maxx)
				x=x+40;
				break;
		}
		setcolor(4);
		rectangle(x+5,y+5,x+35,y+25);
	}while(1);
}