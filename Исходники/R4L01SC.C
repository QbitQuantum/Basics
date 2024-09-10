void main()
{
int gd=VGA,gm=VGAHI,errorcode,area,i,j,play=1,rndplay,rac,r,ch,chh,n=1,speed=151,sp=1,si=1,carx,cary,gear=0,aspeed,booster=100,drumx,drumy,drumv,drumx1,drumy1,spp,coin=200;
int life_=10;
int fire=20;
char info[4];
int soun;
char *buff;
char *fir;
char *boost;
int mouse=23;
int x,y,button;


char *tyre1;
float feul=100;
char *car1buf;
char *pcar4buf;
char *fcar5buf;

int recsize;
FILE *fp;
struct record
{
int coins;
int lifes;
float feuls;
int speeds;
int boosters;
int gear_;
int fire_;
}rec;

recsize=sizeof(rec);

initgraph(&gd,&gm,"c:\bagger");
errorcode = graphresult();
if (errorcode != grOk)
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();

   exit(1);
}
fp=fopen("c:\\rruunn.r4l","r");
fread(&rec,recsize,1,fp);
coin=rec.coins;
feul=rec.feuls;
speed=rec.speeds;
booster=rec.boosters;
gear=rec.gear_;
fire=rec.fire_;
life_=rec.lifes;
fclose(fp);
remove("c:\\rruunn.r4l");

if(coin>0 && feul>0 && life_>0)
{

//geting car's image*****************************************

  setcolor(RED);
  settextstyle(8,1,4);
  outtextxy(100,100+60,"You have :  ");

  car(125,75);
  area=imagesize(85,15,165,405);
  buff=malloc(area);
  getimage(85,15,165,405,buff);
  putimage(85,15,buff,XOR_PUT);




setcolor(8);
setfillstyle(1,8);
bar((getmaxx()/2)-130,0,(getmaxx()/2)+130,getmaxy());
roadstru();
basicstructure1();
sean1();
gears(5);
speedgrp(151-speed);
feulgrp(100);
coingrp(200);
boostergrp(100);
firee(20);
lifee(10);
car(250,400);
setcolor(WHITE);
setfillstyle(1,WHITE);
for(i=-2000;i<+25000;i+=100)
bar((getmaxx()/2)-5,i,(getmaxx()/2)+5,i+80);

delay(1000);

setcolor(getbkcolor());
setfillstyle(1,getbkcolor());
for(i=1;i<320;i++)
{
bar(getmaxx()/2,0,(getmaxx()/2)-i,getmaxy());
bar(getmaxx()/2,0,(getmaxx()/2)+i,getmaxy());
delay(5);
}

delay(1000);



setcolor(YELLOW);
settextstyle(7,0,15);
outtextxy(100-20,100,"R");

settextstyle(7,0,15);
outtextxy(495-20,100,"E");

setcolor(LIGHTBLUE);
settextstyle(7,0,7);
outtextxy(198-20,130,"UN   LIF");

setcolor(BLUE);
setlinestyle(0,0,3);
line(275,155,385,155);
line(275-2,160,385-2,160);
line(275-4,165,385-4,165);
line(275-6,170,385-6,170);
line(275-8,175,385-8,175);
line(275-9,180,385-9,180);
line(275-10,185,385-10,185);
line(275-12,190,385-12,190);

setcolor(YELLOW);
settextstyle(10,0,7);
outtextxy(295,95,"4");


setcolor(LIGHTBLUE);
for(i=1;i<=465;i++)
{
line(80,228,80+i,228);
delay(5);
}
for(i=1;i<20;i++)
{
line(80,228+i,545,228+i);
delay(7);
}
delay(500);
setcolor(LIGHTRED);
settextstyle(8,0,5);
setusercharsize(2,1,1,2);
textdisp1(80,225,"Run For Life",RED,LIGHTRED);

setcolor(LIGHTRED);
settextstyle(8,0,6);
setusercharsize(2,1,1,1);
textdisp1(80,325,"Stage Clear !!!",LIGHTBLUE,BLUE);

delay(2000);
setcolor(getbkcolor());
setfillstyle(1,getbkcolor());
for(i=1;i<=getmaxx();i++)
{
bar(0,0,0+i,getmaxy());
delay(5);
}



for(i=1;i<450;i+=10)
{
putimage(50,getmaxy()-i,buff,XOR_PUT);
delay(5);
putimage(50,getmaxy()-i,buff,XOR_PUT);
}
putimage(50,getmaxy()-450,buff,XOR_PUT);

	setcolor(YELLOW);
	settextstyle(8,0,2);
	outtextxy(200,200,"Coin left : ");
	outtextxy(220,240,"Life left : ");
	outtextxy(200,280,"Fuel left : ");
	outtextxy(220,320,"Booster left : ");
	outtextxy(200,360,"Fire left : ");

	for(i=1;i<=coin;i++)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	bar(350,200,400,250);
	setcolor(YELLOW);
	sprintf(info,"%d",i);
	outtextxy(350,200,info);
	sound(500);
	delay(50);
	nosound();
	}
	for(i=1;i<=life_;i++)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	bar(400,240,450,290);
	setcolor(YELLOW);
	sprintf(info,"%d",i);
	outtextxy(400,240,info);
	sound(400);
	delay(50);
	nosound();
	}
	for(i=1;i<=feul;i++)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	bar(350,280,400,330);
	setcolor(YELLOW);
	sprintf(info,"%d",i);
	outtextxy(350,280,info);
	sound(500);
	delay(50);
	nosound();
	}
	for(i=1;i<=booster;i++)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	bar(400,320,450,370);
	setcolor(YELLOW);
	sprintf(info,"%d",i);
	outtextxy(400,320,info);
	sound(400);
	delay(50);
	nosound();
	}
	for(i=1;i<=fire;i++)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	bar(350,360,400,410);
	setcolor(YELLOW);
	sprintf(info,"%d",i);
	outtextxy(350,360,info);
	sound(500);
	delay(50);
	nosound();
	}
	setcolor(LIGHTBLUE);
	setfillstyle(1,LIGHTBLUE);
	for(i=1;i<400;i++)
	{
	bar(200,50,200+i,150);
	delay(2);
	}
	setcolor(YELLOW);
	rectangle(200,50,600,150);
	setcolor(LIGHTRED);
	rectangle(200+5,50+5,600-5,150-5);
	setcolor(RED);
	settextstyle(3,0,3);
	textdisp(220,60,"Do u accept the next challange");
	setcolor(LIGHTRED);
	rectangle(215,110,400,135);
	rectangle(410,110,585,135);
	setcolor(RED);
	rectangle(215+2,110+2,400-2,135-2);
	rectangle(410+2,110+2,585-2,135-2);
	settextstyle(8,0,1);
	outtextxy(235,106,"Yes, I accept !!!");
	outtextxy(435,106,"No, I Quit");

	change(c);
	show();

	while(mouse==23)
	{
	show();
	moupos(&button,&x,&y);
	if((button & 1)==1)
	{
	if(x>410 && x<585 && y>110 && y<135)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	for(i=1;i<=getmaxx();i++)
	{
	bar(0,0,0+i,getmaxy());
	delay(5);
	}
	hide();
	//one step here
	setcolor(RED);
	settextstyle(4,0,8);
	outtextxy(180,200,"Looser !!!");
	coin=0;
	feul=0;
	speed=0;
	booster=0;
	gear=0;
	fire=0;
	life_=0;
	mouse=0;
	delay(1000);
	//************************************************************************
setfillstyle(8,WHITE);            //background color and style
bar(1,1,getmaxx(),getmaxy());

setfillstyle(7,YELLOW);      //bagger plate
bar(150,5,500,55);

setcolor(BLUE);
for(i=1;i<=5;i++)
{                          //border of bagger plate
setfillstyle(1,BLUE);
rectangle(150-i,5-i,500+i,55+i);
}

settextstyle(1,0,5);
setcolor(WHITE);          // the bagger writen
outtextxy(200,3,"Run 4 Life");


setcolor(WHITE);          //work place designed
setfillstyle(1,WHITE);
bar(100,100,550,350);


setcolor(BLUE);
for(i=1;i<=5;i++)
{                           //work place border
rectangle(100-i,100-i,550+i,350+i);
}


setcolor(getbkcolor());                 //man's face
ellipse(300,190,0,360,35,40);

setfillstyle(1,getbkcolor());        //man's hat
for(i=1;i<=33;i++)
{
arc(300,172,0,180,i);
}


for(i=1;i<=12;i+=2)
{
 setlinestyle(0,0,0);                    //his hair
 arc(322-i,195,150,200,50);
}
for(i=1;i<=10;i+=5)                    //his hair
{
 setlinestyle(0,0,3);
 arc(322-i,195,150,200,50);
}


for(i=1;i<=12;i+=2)
{
 setlinestyle(0,0,0);                    //his hair
 arc(277+i,195,338,30,50);
}
for(i=1;i<=10;i+=5)                    //his hair
{
 setlinestyle(0,0,3);
  arc(277+i,195,338,30,50);
}

fillellipse(285,185,18,10);   //his eye masks
fillellipse(315,185,18,10);

setcolor(WHITE);           //his eye
setfillstyle(1,WHITE);
fillellipse(285,185,5,1);
fillellipse(315,185,5,1);

setcolor(getbkcolor());
setfillstyle(1,getbkcolor());
fillellipse(285,185,1,1);    //his eye ball
fillellipse(315,185,1,1);

 setlinestyle(0,0,0);   //his nose
line(295,192,292,205);
line(302,192,304,205);
line(292,205,304,205);

for(i=1;i<6;i+=1)             //his mooch
arc(300,232,60,120,20+i);

 setlinestyle(0,0,3);
line(288,210,280,225);       //his mooch
line(311,210,318,225);

setlinestyle(0,0,0);
arc(300,205,230,310,12);     //his mouth
arc(300,227,60,120,13);

setlinestyle(0,0,3);
for(i=1;i<=10;i+=4)         //his dadhi
line(295+i,220,295+i,230);



setlinestyle(0,0,0);
line(285,227,285,240);  //his neck
line(315,227,315,240);

setlinestyle(0,0,3);
line(285,240,235,249);    //his  coat base and right hand
line(315,240,342,249);
line(230,255,250,320);
arc(237,255,90,180,6);
line(250,320,340,310);
line(270,270,275,290);
line(275,290,330,285);
setlinestyle(0,0,3);
line(330,285,340,310);
line(325,285,335,310);
setlinestyle(0,0,0);


setlinestyle(0,0,0);
arc(340,330,70,100,40);
arc(340,335,70,90,40);
arc(340,340,70,90,40);     //his finger
arc(340,345,70,90,40);
arc(340,350,70,90,40);
arc(315,305,350,20,40);
setlinestyle(0,0,3);

line(342,200,342,290);
line(365,200,350,290);
arc(355,232,71,110,35); //his stick
line(342,310,340,320);
line(347,310,349,320);
line(340,320,349,320);

line(285,240,320,250);//his left hand
line(315,240,305,245);
line(320,250,323,285);
circle(310,260,2);
circle(311,270,2);
circle(312,280,2);
line(356,252,360,253);
line(360,253,365,328);
line(330,270,333,290);
line(365,328,280,318);


setcolor(getbkcolor());
setlinestyle(0,0,3);
delay(1000);
for(j=1;j<=250;j++)
{
for(i=1;i<450;i+=30)
{
line(100+i,100,100+i,100+j);
line(103+i,100,103+i,100+j);
}
delay(5);
}
delay(1000);
setcolor(BLUE);
settextstyle(10,0,3);
outtextxy(200,200,"Arrested");
rectangle(190,210,390,250);
delay(1500);
setcolor(getbkcolor());
setlinestyle(0,0,3);
for(i=1;i<=450;i++)
{
line(100,220,100+i,220);
delay(5);
}
for(i=1;i<120;i++)
{
line(100,220-i,550,220-i);
line(100,220+i,550,220+i);
delay(20);
}
setcolor(getbkcolor());
setfillstyle(1,getbkcolor());
bar(100,340,550,350);
settextstyle(8,0,5);
setcolor(RED);
textdisp(150,200,"You Loose");

delay(1000);
setcolor(getbkcolor());
setfillstyle(1,getbkcolor());
for(i=1;i<350;i++)
{
bar(getmaxx()/2,0,(getmaxx()/2)-i,getmaxy());
bar(getmaxx()/2,0,(getmaxx()/2)+i,getmaxy());
delay(5);
}
	//**************************************************************************
	}
	else if(x>215 && x<400 && y>110 && y<135)
	{
	setcolor(getbkcolor());
	setfillstyle(1,getbkcolor());
	for(i=1;i<=getmaxx();i++)
	{
	bar(0,0,0+i,getmaxy());
	delay(5);
	}
	hide();
	setcolor(LIGHTGREEN);
	settextstyle(4,0,8);
	outtextxy(180,200,"Bravo !!!");
	mouse=0;
	}
	}
	}

}
//*********************************************************************************************
rec.coins=coin;
rec.feuls=feul;
rec.speeds=speed;
rec.gear_=gear;
rec.lifes=life_;
rec.fire_=fire;
rec.boosters=booster;
fp=fopen("c:\\rruunn.r4l","w");
fwrite(&rec,recsize,1,fp);
fclose(fp);
//closegraph();
delay(1500);
}