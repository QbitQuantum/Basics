void controls()
{
   int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,i;
   setcolor(0);
   rectangle(61,83,410,259);
   setfillstyle(1,9);
   floodfill(107,137,0);
   arc(62,166,270,90,16);
   setfillstyle(1,6);
   floodfill(68,165,0);

   x1=62;
   y1=67;
   x2=84;
   y2=83;
   x3=73;
   y3=73;
   for(i=0;i<8;i++)
   {
     rectangle(x1,y1,x2,y2);
     x1+=46;
     x2+=46;
     setfillstyle(1,14);
     floodfill(x3,y3,0);
     x3+=46;
   }
   x1=62;
   y1=259;
   x2=84;
   y2=275;
   x3=72;
   y3=267;
   for(i=0;i<8;i++)
   {
     rectangle(x1,y1,x2,y2);
     x1+=46;
     x2+=46;
     setfillstyle(1,14);
     floodfill(x3,y3,0);
     x3+=46;
   }
   outtextxy(70,264,"1");
   outtextxy(65,289,"A1");
   outtextxy(116,264,"2");
   outtextxy(112,289,"B1");
   outtextxy(163,264,"3");
   outtextxy(161,289,"Y1");
   outtextxy(207,264,"4");
   outtextxy(205,289,"A2");
   outtextxy(253,264,"5");
   outtextxy(250,289,"B2");
   outtextxy(299,264,"6");
   outtextxy(297,289,"Y2");
   outtextxy(343,264,"7");
   outtextxy(340,289,"GND");
   outtextxy(390,264,"8");
   outtextxy(387,289,"Y");
   outtextxy(65,74,"16");
   outtextxy(62,55,"Vcc");
   outtextxy(111,74,"15");
   outtextxy(112,54,"A4");
   outtextxy(158,74,"14");
   outtextxy(159,54,"B4");
   outtextxy(204,74,"13");
   outtextxy(205,54,"Y4");
   outtextxy(250,74,"12");
   outtextxy(248,54,"A3");
   outtextxy(295,74,"11");
   outtextxy(297,54,"B3");
   outtextxy(340,74,"10");
   outtextxy(337,54,"Y3");
   outtextxy(394,74,"9");
   outtextxy(387,54,"bv");
   settextstyle(1,0,4);
   setlinestyle(0,0,3);
   setcolor(15);
   line(440,60,599,60);
   line(440,60,440,220);
   setcolor(0);
   line(440,220,599,220);
   line(599,220,599,60);
   setlinestyle(1,0,1);
   setfillstyle(1,0);
   setcolor(0);
   bar(447,63,592,90);
   settextstyle(1,0,1);
   setcolor(14);
   outtextxy(460,68,"RESULTS");
   setcolor(2);
   for(y1=102,i=0;i<4;i++)
   {
     circle(462,y1,10);
     setfillstyle(1,4);
     floodfill(462,y1,2);
     y1+=30;
   }
   setlinestyle(0,0,1);

   setcolor(15);
   line(120,400,190,400);
   line(120,400,120,450);
   setcolor(0);
   line(120,450,190,450);
   line(190,450,190,400);
   setcolor(0);
   outtextxy(130,410,"Index");
   setcolor(15);
   line(250,400,320,400);
   line(250,400,250,450);
   setcolor(0);
   line(250,450,320,450);
   line(320,450,320,400);
   outtextxy(260,410,"Exit");
   settextstyle(1,0,3);
   setcolor(RED);
   outtextxy(150,320,"PIN DIAGRAM");
   setlinestyle(0,0,3);
   line(150,350,297,350);

   setlinestyle(0,0,3);
   setcolor(15);
   line(420,270,600,270);
   line(420,270,420,440);
   setcolor(0);
   line(420,440,600,440);
   line(600,440,600,270);

   bar(422,272,596,310);
   setcolor(14);
   outtextxy(425,280,"Truth Table");
   setcolor(MAGENTA);
   line(430,320,590,320);
   line(430,320,430,430);
   line(430,430,590,430);
   line(590,430,590,320);
   line(530,320,530,430);
   setcolor(BROWN);
   settextstyle(0,0,1);
   outtextxy(460,330,"INPUTS");
   outtextxy(540,3330,"OUTPUT");
   setcolor(MAGENTA);
   line(430,345,590,345);
   line(480,345,480,430);
   setcolor(12);
   outtextxy(450,355,"L");
   outtextxy(500,355,"L");
   outtextxy(560,355,"L");
   outtextxy(450,375,"L");
   outtextxy(500,375,"H");
   outtextxy(560,375,"L");
   outtextxy(450,395,"H");
   outtextxy(500,395,"L");
   outtextxy(560,395,"L");
   outtextxy(450,415,"H");
   outtextxy(500,415,"H");
   outtextxy(560,415,"H");
   setcolor(MAGENTA);
   line(430,370,590,370);
   line(430,390,590,390);
   line(430,410,590,410);
   line(430,430,590,430);
}