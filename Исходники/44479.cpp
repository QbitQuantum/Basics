static
BOOL xxRegisterWndClasses(LPCSTR menuName)
{
    POCDEBUG_BREAK();
    CHAR buf[0x10] = { 0 };
    for (LONG i = 0; i < tmpTimes; i++)
    {
        WNDCLASSEXA Class = { 0 };
        sprintf(buf, "CLS_%d", i);
        Class.lpfnWndProc = DefWindowProcA;
        Class.lpszClassName = buf;
        Class.lpszMenuName = menuName;
        Class.cbSize = sizeof(WNDCLASSEXA);
        if (!RegisterClassExA(&Class))
        {
            return FALSE;
        }
    }
    return TRUE;
}