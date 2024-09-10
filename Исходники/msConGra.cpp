//-----------------------------------------------------------------------------
void graphics::set_cursor_pos(int xCo, int yCo)
{
	COORD cursor_pos = {xCo-1, yCo-1};
	SetConsoleCursorPosition(hConsole, cursor_pos);
}