static void condraw (float x, float y)
{
	lineto(x,y);
	if (++pathcount>PATHMAX) {
		stroke();
		moveto(x,y);
		pathcount = 0;
	}
}