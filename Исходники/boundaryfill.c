void boundary_fill(int x,int y,int fcolor,int bcolor)
{
	if ((getpixel(x,y)!=fcolor) && (getpixel(x,y)!=bcolor))
	{
		putpixel(x, y, fcolor);
		boundary_fill(x+1,y,fcolor,bcolor);
		boundary_fill(x-1,y,fcolor,bcolor);
		boundary_fill(x,y-1,fcolor,bcolor);
		boundary_fill(x,y+1,fcolor,bcolor);
	}
}