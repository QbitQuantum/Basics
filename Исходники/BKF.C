void secure()
{
char cha,daff[30];int s=0;
setcolor(15);settextstyle(2,0,5);
cleardevice();setbkcolor(0);
bk();setcolor(15);rectangle(0,0,getmaxx(),getmaxy());
//outtextxy(250,14,"username");rectangle(320,13,600,28);
outtextxy(250,40,"password");rectangle(320,40,600,55);

settextstyle(2,0,4);cha=0;
while(cha!=13)
{
if(kbhit())
{
cha=getch();
if(cha!=8 && s<=200)
{sprintf(daff,"%c",cha);outtextxy(330+s,14,daff);
s+=10;}

if(cha==8 && s>0 && s<=210)
{setfillstyle(0,1); bar(330+s,14,330+s-10,24);s-=10;}

}}

cha=0;
s=0;

while(cha!=13)
{
if(kbhit())
{
cha=getch();
if(cha!=8 && s<200)
{sprintf(daff,"%c",cha);outtextxy(330+s,40,"*");s+=10;}

if(cha==8 && s>0 && s<=210)
{setfillstyle(0,1); bar(330+s,42,330+s-10,50);s-=10;}
}}
cha=0;

cleardevice();setbkcolor(0);
setcolor(3);settextstyle(2,0,5);
outtextxy(40,100,"Payment mode");
setcolor(4);
outtextxy(40,130,"credit");
setcolor(15);
outtextxy(40,140,"debit");
outtextxy(40,150,"net banking.");

pay=0;cha=0;
while(cha!=27)
{
if(kbhit())
{ cha=getch();
if(cha==80 && pay<2)
{pay++;select_pay(pay);}
if(cha==72 && pay>0)
{pay--;select_pay(pay);}
if(cha==13)
break;
}}

}