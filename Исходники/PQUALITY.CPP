	void hit()
	{
		int flag=0;

		if(dir==1)
		if (getpixel(x+radius+BSPEED+0.5,y)==BLUE)
		flag=1;

		if(dir==2)
		if(getpixel(x,y+radius+BSPEED+0.5)==BLUE)
		flag=1;

		if(dir==3)
		if(getpixel(x-radius-BSPEED-0.5,y)==BLUE)
		flag=1;

		if(dir==4)
		if(getpixel(x,y-radius-BSPEED-0.5)==BLUE)
		flag=1;


		if(flag==1)
		{
			setcolor(BLACK);
			circle(x,y,radius);
			on_screen=0;
		}
	}