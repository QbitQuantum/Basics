int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Enable assertion failure message box
    // http://msdn.microsoft.com/en-us/library/sas1dkb2.aspx
    _set_error_mode(_OUT_TO_MSGBOX);
#ifdef _MSC_VER
    // Enable abort message box
    // http://msdn.microsoft.com/en-us/library/e631wekh.aspx
    _set_abort_behavior(0, _CALL_REPORTFAULT);
#endif
    assert(2 + 2 == 5);
    return 0;
}