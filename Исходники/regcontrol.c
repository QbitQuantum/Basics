BOOL WINAPI RegisterSystemControls(VOID)
{
    WNDCLASSEXW WndClass;
    UINT i;
    ATOM atom;

    if (RegisterDefaultClasses) return TRUE;

    ZeroMemory(&WndClass, sizeof(WndClass));

    WndClass.cbSize = sizeof(WndClass);

    for (i = 0; i != sizeof(g_SysClasses) / sizeof(g_SysClasses[0]); i++)
    {
        WndClass.lpszClassName = g_SysClasses[i].desc->name;

        // Set Global bit!
        WndClass.style = g_SysClasses[i].desc->style|CS_GLOBALCLASS;
        WndClass.lpfnWndProc = g_SysClasses[i].desc->procW;
        WndClass.cbWndExtra = g_SysClasses[i].desc->extra;
        WndClass.hCursor = LoadCursorW(NULL, g_SysClasses[i].desc->cursor);
        WndClass.hbrBackground= g_SysClasses[i].desc->brush;

        atom = RegisterClassExWOWW( &WndClass,
                                     0,
                                     g_SysClasses[i].fnid,
                                     0,
                                     FALSE);
        if (atom)
           RegisterDefaultClasses |= ICLASS_TO_MASK(g_SysClasses[i].ClsId);
    }

    return TRUE;
}