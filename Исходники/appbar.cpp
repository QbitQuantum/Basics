BOOL CAppBar::AppBar_UnRegister()
{
  
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = pHandler;

    g_fAppRegistered = !SHAppBarMessage(ABM_REMOVE, &abd);
        
    return !g_fAppRegistered;
}        