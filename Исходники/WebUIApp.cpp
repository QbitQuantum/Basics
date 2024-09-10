void onTitleChanged(const wkeClientHandler* clientHandler, const wkeString title)
{
    HWND hWnd = 0;
    Ogre::Root::getSingleton().getAutoCreatedWindow()->getCustomAttribute("WINDOW", &hWnd);
    SetWindowTextW(hWnd, wkeToStringW(title));
}