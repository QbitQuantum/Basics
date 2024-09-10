void Font_bitmap::Print_vec(int x, int y, const vec &a, char *meno)
{
	if(meno!=NULL)
	{
		Print(x, y, meno,0);
		x += strlen(meno)+1;
	}
	
	gcvt( (double)a.x, 2, text);
	Print(x,y,text,0);
	x+=10;
	gcvt( (double)a.y, 2, text);
	Print(x,y,text,0);
	x+=10;
	gcvt( (double)a.z, 2, text);
	Print(x,y,text,0);
}