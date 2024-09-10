void loading()
{
int i,j,x,y;

setbkcolor(6);

	x=getmaxx()/2;
	y=getmaxy()/2;
	for(j=30;j<200;j++)
	{
		delay(10);
		setcolor(j/20);
		arc(x,y,0,180,j-10);
	}
settextstyle(3,0,6);
outtextxy(150,250,"!..DOGDE IT..!");
settextstyle(4,0,4);
outtextxy(250,340,"LOADING");
for(i=100; i<600; i++)
{
bar(i,380,i,400);
delay(10);
}
}