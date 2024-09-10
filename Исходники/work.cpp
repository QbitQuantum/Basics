void runkernel(void)
{
	cleardevice();
	setbkcolor(0);

	int id,l,count=0;
	Control.First=0;
	Control.Free=50;
	id=Number+1;
	while((Control.Free<50)||(Number==-1))
	{
		while(bioskey(1)!=0)
		{
			count++;
			bioskey(0);
			biuldwait(id);
			id++;
			Number++;
		}
		if((wt==wh&&wh==0)||(wt!=wh))	biuldmem();/*Biuld all can*/
		cleardevice();
		setbkcolor(0);
		drawgrid();
		run();
		finish();
		compress();
		display();
		delay(2000);
	}
	setcolor(0);
	for(int a=0;a<629;a++)
	{
		moveto(a,390);
		lineto(a,425);
		moveto(a,445);
		lineto(a,460);
	}
	setcolor(YELLOW);
	outtextxy(180,450,"All the processes have been done!");
	getch();
}