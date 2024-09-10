void TaskManager_OnOptionsShow16BitTasks(void)
{
    HMENU    hMenu;
    HMENU    hOptionsMenu;

    hMenu = GetMenu(hMainWnd);
    hOptionsMenu = GetSubMenu(hMenu, OPTIONS_MENU_INDEX);

    /*
     * FIXME: Currently this is useless because the
     * current implementation doesn't list the 16-bit
     * processes. I believe that would require querying
     * each ntvdm.exe process for it's children.
     */

    /*
     * Check or uncheck the show 16-bit tasks menu item
     */
    if (GetMenuState(hOptionsMenu, ID_OPTIONS_SHOW16BITTASKS, MF_BYCOMMAND) & MF_CHECKED)
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_SHOW16BITTASKS, MF_BYCOMMAND|MF_UNCHECKED);
        TaskManagerSettings.Show16BitTasks = FALSE;
    }
    else
    {
        CheckMenuItem(hOptionsMenu, ID_OPTIONS_SHOW16BITTASKS, MF_BYCOMMAND|MF_CHECKED);
        TaskManagerSettings.Show16BitTasks = TRUE;
    }

    /*
     * Refresh the list of processes.
     */
    RefreshProcessPage();
}