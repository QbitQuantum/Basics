void hint::SetRectangle(int x, int y, int width, int height)
{
	SetRect(&rectangle, x, y, x+width, y+height);
}