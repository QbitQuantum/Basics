static bool wndRegisterClass(HINSTANCE              theInstance,
                             const StStringUtfWide& theClassName) {
    WNDCLASSW aClass;
    aClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    aClass.lpfnWndProc   = (WNDPROC )wndProcWrapper;
    aClass.cbClsExtra    = 0;
    aClass.cbWndExtra    = 0;
    aClass.hInstance     = theInstance;
    aClass.hIcon         = LoadIconW(theInstance, L"A");
    aClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    aClass.hbrBackground = NULL;
    aClass.lpszMenuName  = NULL;
    aClass.lpszClassName = theClassName.toCString();
    return (RegisterClassW(&aClass) != 0);
}