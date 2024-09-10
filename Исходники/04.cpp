void clipline(dcpt winmin,dcpt winmax,wcpt2 p1,wcpt2 p2)
{
	unsigned char encode(wcpt2,dcpt,dcpt);
	unsigned char code1,code2;
	int done = 0 , draw = 0;
	float m;
	void swapcode(unsigned char *c1,unsigned char *c2);
	void swappts(wcpt2 *p1,wcpt2 *p2);

	while(!done)
	{
		code1 = encode(p1,winmin,winmax);
		code2 = encode(p2,winmin,winmax);
		if(ACCEPT(code1,code2))
		{
			draw = 1;
			done = 1;
		}
		else if(REJECT(code1,code2))
			done = 1;
		else if(INSIDE(code1))
		{
				swappts(&p1,&p2);
				swapcode(&code1,&code2);
		}
		if(code1 & LEFT_EDGE)
		{
				p1.y += (winmin.x - p1.x) *  (p2.y - p1.y) / (p2.x - p1.x);
				p1.x = winmin.x;
		}
		else if(code1 & RIGHT_EDGE)
		{
				p1.y += (winmax.x - p1.x) *  (p2.y - p1.y) / (p2.x - p1.x);
				p1.x = winmax.x;
		}
		else if(code1 & TOP_EDGE)
		{
			if(p2.x != p1.x)
				p1.x += (winmin.y - p1.y) *  (p2.x - p1.x) / (p2.y - p1.y);
				p1.y = winmin.y;
		}
		else if(code1 & BOTTOM_EDGE)
		{
			if(p2.x != p1.x)
				p1.x += (winmax.y - p1.y) *  (p2.x - p1.x) / (p2.y - p1.y);
				p1.y = winmax.y;
		}
    }
    if(draw)
    {
	setcolor(5);
	line(p1.x,p1.y,p2.x,p2.y);
    }
}