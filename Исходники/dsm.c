static BOOL dsm_RegisterWindowClasses(void)
{
    WNDCLASSA cls;
    BOOL rc;

    cls.style = 0;
    cls.lpfnWndProc = DefWindowProcA;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPCSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "TWAIN_dsm_class";

    rc = RegisterClassA(&cls);
    ok(rc, "RegisterClassA failed: le=%u\n", GetLastError());
    return rc;
}