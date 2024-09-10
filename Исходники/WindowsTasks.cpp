bool IsShellWindow(HWND window)
{
    if(!IsWindow(window) || !IsWindowVisible(window))
    {
        return false;
    }
    if(GetAncestor(window, GA_PARENT) != GetDesktopWindow())
    {
        return false;
    }

    RECT clientRect;
    GetClientRect(window, &clientRect);
    if(clientRect.right - clientRect.left <= 1 || clientRect.bottom - clientRect.top <= 1)
    {
        return false;
    }
    
    char name[256] = {'\0'};
    GetWindowText(window, name, 256);
    String sName = name;
    if(sName.Length() == 0 || sName == "Start")
    {
        return false;
    }

    return true;
}