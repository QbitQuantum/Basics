void main()
{
char a;
float x=10,y,x1,y1,n=1.0;
int m=3;
int max=0,k;
int count=1,score=0;
char l[33],r[33];
FILE *f;
char *o="Lives ";
char *q="Score";
int gd=DETECT,gm,b;
clrscr();
initgraph(&gd,&gm,"c:\\tc\\bgi");
setbkcolor(GREEN);
while(!kbhit())
{
setcolor(BLUE);
settextstyle(7,HORIZ_DIR,6);
outtextxy(120,180,"CATCH THE EGG");
setcolor(WHITE);
settextstyle(7,HORIZ_DIR,1);
outtextxy(180,250,"PRESS ANY KEY TO START");
settextstyle(8,HORIZ_DIR,1);
outtextxy(440,390,"C Project By");
outtextxy(440,410,"Abhinav");
outtextxy(440,430,"Nikhil");
outtextxy(440,450,"Nitish");
settextstyle(1,HORIZ_DIR,1);
setcolor(WHITE);
outtextxy(30,395,"Press Z to move left");
outtextxy(30,415,"Press M to move right");
outtextxy(30,435,"Press Q to QUIT");
delay(150);
setcolor(BLACK);
settextstyle(7,HORIZ_DIR,1);
outtextxy(180,250,"PRESS ANY KEY TO START");
delay(150);
}
cleardevice();
setbkcolor(BLACK);
y=440.0;
while(a!='q'&& m!=-1)
{
sprintf(l,"%s %d",o,m);
sprintf(r,"%s %d",q,score);
x1=rand() % 400 + 10;
y1=10;
cleardevice();
while(y1<440 && a!='q')
{
setcolor(WHITE);
settextstyle(9,HORIZ_DIR,1);
outtextxy(450,20,l);
outtextxy(450,50,r);
setcolor(RED);
setfillstyle(1,YELLOW);
rectangle(x,y,x+20,y+15);
floodfill(x+1,y+1,RED);
b=getpixel(x+50,y+50);
setcolor(WHITE);
setfillstyle(1,WHITE);
ellipse(x1,y1,0,360,4,15);
floodfill(x1,y1,WHITE);
setfillstyle(SOLID_FILL,b);
setcolor(b);
if(kbhit())
{
a=getch();
if(a=='q')break;
rectangle(x,y,x+20,y+15);
floodfill(x+1,y+1,b);
if(a=='m')
if(x<getmaxx())
x+=15.0;
else
x=0;
if(a=='z')
if(x>0)
x-=15.0;
else
x=getmaxx();
}
setcolor(BLACK);
setfillstyle(1,BLACK);
ellipse(x1,y1,0,360,4,15);
delay(5);
floodfill(x1,y1,BLACK);
if(y1-440>-5)
{
if(x1-x<30 && x1-x>-10)
{
setcolor(YELLOW);
setfillstyle(1,YELLOW);
ellipse(x1,y1,0,360,4,15);
floodfill(x1,y1,YELLOW);
setcolor(BLACK);
setfillstyle(1,BLACK);
ellipse(x1,y1,0,360,4,15);
delay(200);
floodfill(x1,y1,BLACK);
score+=3;
break;
}
else
m--;
break;
}
y1=y1+n;
}
if(count%4==0)
{
n+=0.2;
}
count++;
}
if(m==-1)
{
cleardevice();
setcolor(RED);
settextstyle(6,HORIZ_DIR,6);
outtextxy(220,200,"GAME OVER");
f=fopen("high.txt","a+");
putw(score,f);
rewind(f);
while(k!=EOF)
{
k=getw(f);
if(k>max)
max=k;
}
fclose(f);
settextstyle(6,HORIZ_DIR,1);
setcolor(WHITE);
sprintf(r,"  Your Score %d",score);
outtextxy(250,290,r);
sprintf(r,"  High Score %d",max);
outtextxy(250,330,r);
delay(2000);
}
closegraph();
}