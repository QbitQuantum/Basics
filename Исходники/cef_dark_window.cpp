// Enforce that the menu has our background color otherwise it 
//  uses the system default color for the menu bar which looks funny
void cef_dark_window::EnforceMenuBackground()
{
    MENUBARINFO mbi = {0};
    mbi.cbSize = sizeof(mbi);
    
    GetMenuBarInfo(OBJID_MENU, 0, &mbi);

    MENUINFO mi = {0};
    mi.cbSize = sizeof(mi);
    mi.fMask = MIM_BACKGROUND;

    ::GetMenuInfo(mbi.hMenu, &mi);
    
    if (mi.hbrBack != mBackgroundBrush) {
        mi.hbrBack = mBackgroundBrush;
        ::SetMenuInfo(mbi.hMenu, &mi);
    }
}