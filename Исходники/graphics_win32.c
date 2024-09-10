/*--------------------------------------
 * Function: registerWindowClass()
 *------------------------------------*/
static void registerWindowClass(void) {
    WNDCLASSEXW wcx = { 0 };

    wchar_t* class_name = wstrdup(ClassName);

    wcx.cbSize        = sizeof(WNDCLASSEXW);
    wcx.style         = CS_HREDRAW | CS_VREDRAW;
    wcx.lpfnWndProc   = WindowProc;
    wcx.cbClsExtra    = 0;
    wcx.cbWndExtra    = 0;
    wcx.hInstance     = GetModuleHandleW(NULL);
    wcx.hIcon         = LoadIconW(NULL, IDI_APPLICATION);
    wcx.hCursor       = LoadCursorW(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcx.lpszMenuName  = NULL;
    wcx.lpszClassName = class_name;
    wcx.hIconSm       = NULL;

    if (!RegisterClassExW(&wcx)) {
        free(class_name);
        error("could not register window class");
    }

    free(class_name);
}