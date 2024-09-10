void unclip()
{
int a;

RECT _screen;

_screen.left = 0;
_screen.top = 0;
_screen.right = GetSystemMetrics(SM_CXSCREEN);
_screen.bottom = GetSystemMetrics(SM_CYSCREEN);

ClipCursor(&_screen);
}