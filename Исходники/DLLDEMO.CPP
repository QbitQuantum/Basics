inline void SetPointer( HWND hWnd, Window *pWindow )
{
    SetWindowWord( hWnd, 0, (WORD) pWindow );
}