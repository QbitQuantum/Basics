static inline int check_delta(int x1,int y1,int w,int h,int x,int y,int *a,int *b,int *c)
{
	int dx=0,dy=0;
	int xx=x,yy=y;
	while((getpixel(x,y)==0)&&(getpixel(x+1,y)==0))
	{
		if(next_2pixel(x1,y1,w,h,&x,&y)>=2)
			return EOB;
	}
	dx=x-xx;
	dy=yy-y;
	if((dx<0)&&(dy>0))
	{
		return EOL;
	}
	if((dx>0)&&(dy>0))
	{
		if(dx>0xfe)
			dx=0xfe;
		if(dy>0xfe)
			dy=0xfe;
		*a=dx;
		*b=dy;
		return DELTA;
	}
	return NOPE;
}