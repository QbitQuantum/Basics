/**
 * Converts an EMENU to a Windows menu object.
 *
 * \param Menu The menu item to convert.
 * \param Flags A combination of the following:
 * \li \c PH_EMENU_CONVERT_ID Automatically assigns a unique identifier to each converted menu item.
 * The resulting mappings are placed in \a Data.
 * \param Data Additional data resulting from the conversion. The data structure must be initialized
 * by PhInitializeEMenuData() prior to calling this function.
 *
 * \return A menu handle. The menu object must be destroyed using DestroyMenu() when it is no longer
 * needed.
 */
HMENU PhEMenuToHMenu(
    _In_ PPH_EMENU_ITEM Menu,
    _In_ ULONG Flags,
    _Inout_opt_ PPH_EMENU_DATA Data
    )
{
    HMENU menuHandle;

    menuHandle = CreatePopupMenu();

    if (!menuHandle)
        return NULL;

    PhEMenuToHMenu2(menuHandle, Menu, Flags, Data);

    if (!(Menu->Flags & PH_EMENU_SEPARATECHECKSPACE))
    {
        MENUINFO menuInfo;

        memset(&menuInfo, 0, sizeof(MENUINFO));
        menuInfo.cbSize = sizeof(MENUINFO);
        menuInfo.fMask = MIM_STYLE;
        menuInfo.dwStyle = MNS_CHECKORBMP;
        SetMenuInfo(menuHandle, &menuInfo);
    }

    return menuHandle;
}