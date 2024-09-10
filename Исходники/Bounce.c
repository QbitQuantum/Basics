void main()
{ int gd=DETECT,gm,i=370;
  char ch;
  clrscr();
  initgraph(&gd,&gm,"C:\\TC\\bgi");
  setbkcolor(WHITE);
  do{
  setcolor(BLUE);
  line(100,400,500,400);
  setcolor(BLUE);
      circle(300,370,30);
     // rectangle(294,365,306,375);
      setfillstyle(1,RED);
      floodfill(300,370,BLUE);
      settextstyle(3,0,1);
      outtextxy(100,410,"Press space to Jump!");
      outtextxy(360,410,"Press x to exit!");
      ch=getch();
      fflush(stdin);
      if(ch==' ')
      { do
       { delay(60);
	cleardevice();
	setcolor(BLUE);
	line(100,400,500,400);
	setcolor(BLUE);
	i=i-50;
	circle(300,i,30);
	setfillstyle(1,RED);
      floodfill(300,i,BLUE);
	}while(i>100);
	 do
       {delay(60);
	cleardevice();
	setcolor(BLUE);
	line(100,400,500,400);
	setcolor(BLUE);
	i=i+50;
	circle(300,i,30);
	setfillstyle(1,RED);
      floodfill(300,i,BLUE);
	}while(i<370);
	cleardevice();
	}
	else
	 break;
	while(kbhit())
	  ch=getch();
	 }while(1);

  cleardevice();
  //getch();
  closegraph();
}