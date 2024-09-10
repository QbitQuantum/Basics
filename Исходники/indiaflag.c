int main()
{
 int gd=DETECT ,gm,xc,yc,r,i;
 char ch;
 initgraph(&gd,&gm,NULL);
//orange
 linedda(100,30,400,30,12);
 linedda(100,30,100,60,12);
 linedda(400,30,400,60,12);
 linedda(100,60,400,60,12);
 for(i=0;i<30;i++)
   linedda(100,30+i,400,30+i,4);

//white
 linedda(100,61,400,61,15);
 linedda(100,61,100,90,15);
 linedda(400,61,400,90,15);
 linedda(100,90,400,90,15); 
 for(i=30;i<61;i++)
   linedda(100,30+i,400,30+i,7);
//green
 linedda(100,91,400,91,10);
 linedda(100,91,100,120,10);
 linedda(400,91,400,120,10);
 linedda(100,120,400,120,10);
  for(i=61;i<90;i++)
   linedda(100,30+i,400,30+i,10);
//circle now
 circle(250,75,15);

 spokes();

 delay(20000); 	
 scanf("%d",&ch);
 closegraph();
 getch();
 return 0;
}