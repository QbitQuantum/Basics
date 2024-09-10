/****************************************************************************
*
*     FUNCTION: WinMain
*
*     PURPOSE:  Main entry point for this app
*
*     PARAMS:   HANDLE hInstance     - This instance
*               HANDLE hPrevInstance - Previous instance
*               LPSTR  lpszCmdLine   - Command Line
*               int    nCmdShow      - Desired window status
*
*     RETURNS:  int - return code
*
* History:
*                July '95 - Created
*
\****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    MSG msg;

    // standard init stuff
    if( ! hPrevInstance )
    {
        if( ! InitApplication( hInstance ) )
        {
            return FALSE;
        }
    }
    if( ! InitInstance( hInstance, nCmdShow ) )
    {
        return FALSE;
    }

    // Standard message loop
    while (GetMessage(&msg, (HWND) NULL, 0, 0)) 
    {
        if( !TranslateMDISysAccel(hMDIClientWnd, &msg) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}