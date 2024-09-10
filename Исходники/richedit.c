/* Registers the window class. */
static BOOL RICHED32_Register(void)
{
    WNDCLASSA wndClass;

    ZeroMemory(&wndClass, sizeof(WNDCLASSA));
    wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
    wndClass.lpfnWndProc = RichEdit10ANSIWndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = sizeof(void *);
    wndClass.hCursor = LoadCursorA(0, (LPSTR)IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszClassName = RICHEDIT_CLASS10A; /* WC_RICHED32A; */

    RegisterClassA(&wndClass);

    return TRUE;
}