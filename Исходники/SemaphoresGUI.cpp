/*********************** husband's face *************************/
void husFace(int i)
{

//int gd=DETECT,gm;
//initgraph(&gdriver,&gmode,"c:\Turboc3\bgi");
setcolor(GREEN);
//setbkcolor(0);
/*-------------------CHIN------------------------*/

ellipse(298-i,244-i,160,380,60,80);

/*----------------- HAIR ------------------------*/

arc(300-i,219-i,400,140,80);
ellipse(355-i,190-i,270,438,10,28);
arc(359-i,188-i,169,265,30);
ellipse(288-i,190-i,180,360,40,20);
ellipse(239-i,193-i,96,370,8,25);

/*---------------Eye Brows-------------------------*/

/*arc(282-i,255-i,89,130,40);
arc(278-i,259-i,80,120,40);
//arc(314-i,255-i,405,92,40);
//arc(319-i,259-i,420,100,40);
line(310-i,215-i,310,220);
line(284-i,215-i,284,219);
  */
/*-------------------Eyes--------------------------*/

setfillstyle(SOLID_FILL,WHITE);
ellipse(320-i,230-i,0,360,10,5);
ellipse(275-i,230-i,0,360,10,5);
fillellipse(320-i,230-i,10,5);
fillellipse(275-i,230-i,10,5);
setfillstyle(SOLID_FILL,BLACK);
ellipse(320-i,230-i,0,360,4,4);
ellipse(275-i,230-i,0,360,4,4);
fillellipse(320-i,230-i,5,5);
fillellipse(275-i,230-i,5,5);

/*------------------Nose----------------------*/

ellipse(280-i,220-i,270,0,10,40);
ellipse(315-i,220-i,180,270,10,40);
ellipse(285-i,260-i,100,285,8,7);
ellipse(310-i,260-i,255,70,8,7);
circle(320-i,230-i,2);
circle(275-i,230-i,2);
arc(297-i,257-i,228,689,15);

/*---------------------MOUTH--------------------*/

ellipse(298-i,290-i,0,360,30,7);
//line(270-i,290-i,326,290);

/*----------------------Ears--------------------*/

ellipse(234-i,240-i,0,330,4,20);
ellipse(362-i,240-i,220,170,4,20);
//getch();
//clearviewport();
//closegraph();
//restorecrtmode();

}