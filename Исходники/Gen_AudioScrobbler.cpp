// Helper method for subclassing Window procedure. If we're not using the correct A/W
// versions, Unicode tracks won't display properly in the taskbar.
WNDPROC SetWndSubClass( HWND hwnd, WNDPROC newproc, WNDPROC* oldproc )
{
    if ( IsWindowUnicode(hwnd) )
    {
        *oldproc = (WNDPROC)GetWindowLongPtrW( hwnd, GWL_WNDPROC );
        return (WNDPROC)SetWindowLongPtrW( hwnd, GWL_WNDPROC, (LONG_PTR)newproc );
    }
    else
    {
        *oldproc = (WNDPROC)GetWindowLongPtrA( hwnd, GWL_WNDPROC );
        return (WNDPROC)SetWindowLongPtrA( hwnd, GWL_WNDPROC, (LONG_PTR)newproc );
    }
}