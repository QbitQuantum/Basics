void Menuer::checkAutorunMenu()
{
    UINT state = GetMenuState(trayMenu_, IDM_AUTORUN, MF_BYCOMMAND);
    bool toCheck = !(state & MF_CHECKED); // revert

    checkMenu(IDM_AUTORUN, toCheck);

    if (toCheck) { autorun_enable(); }
    else { autorun_cancel(); }
}