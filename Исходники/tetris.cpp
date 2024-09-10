// Console cursor ÀÌµ¿.
void gotoxy(int x, int y)
{
	COORD pos = { static_cast< short >( x ), static_cast< short >( y ) };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}