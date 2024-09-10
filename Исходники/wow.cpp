void rect(int i)
{
	setbkcolor(0);

       if(300+i<=0)
       keyhit(i+=10);
	else if(350+i>=640)
	keyhit(i-=10);
	else
	{setlinestyle(DASHED_LINE,1,2);
	 rectangle(300+i,429,350+i,436);
	 setlinestyle(SOLID_LINE,1,2);
	 rectangle(310+i,419,340+i,429);
	 rectangle(322+i,409,328+i,419);
	 setcolor(GREEN);
	 line(10,438,630,438);
	 setfillstyle(SOLID_FILL,6);
	 bar(10,440,630,445);floodfill(12,441,6);
	 setcolor(1);
	 settextstyle(11,0,4);
	 outtextxy(80,460,"Designed and Developed by <<::>> Tejendra Singh & Shubham Singh");
	 setcolor(RED);
	 settextstyle(11,0,4);
	 outtextxy(15,20,"Score:");
	 setcolor(WHITE);
	 circle(303+i,432,3);
	 circle(312+i,432,3);
	 circle(324+i,432,3);
	 circle(336+i,432,3);
	 circle(347+i,432,3);
		 setcolor(i+1);
	 outtextxy(10,50,".");  setcolor(i+1);
	 outtextxy(20,100,"."); setcolor(i+2);
	 outtextxy(30,150,"."); setcolor(i+3);
	 outtextxy(50,50,".");  setcolor(i+4);
	 outtextxy(90,200,".");  setcolor(i+5);
	 outtextxy(420,277,"."); setcolor(i+6);
	 outtextxy(150,110,"."); setcolor(i+7);
	 outtextxy(350,300,"."); setcolor(i+8);
	 outtextxy(200,140,"."); setcolor(i+9);
	 outtextxy(550,280,"."); setcolor(i+10);
	 outtextxy(300,250,"."); setcolor(i+11);
	 outtextxy(560,260,"."); setcolor(i+12);
	 outtextxy(400,70,".");  setcolor(i+13);
	 outtextxy(15,239,".");  setcolor(i+14);
	 outtextxy(450,166,"."); setcolor(i+15);
	  outtextxy(300,59,"."); setcolor(i+16);
	 outtextxy(500,80,".");  setcolor(i+17);
	  outtextxy(290,95,"."); setcolor(i+18);
	 outtextxy(530,89,".");  setcolor(i+19);
	   outtextxy(150,305,".");
	 setcolor(RED);
	 }
}