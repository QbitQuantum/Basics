static VOID
EnumChildDevices(HWND hTreeView,
                 HTREEITEM hRoot,
                 DEVINST dnParentDevInst,
                 BOOL bShowHidden)
{
    HTREEITEM hDevItem;
    DEVINST dnDevInst;
    CONFIGRET cr;

    cr = CM_Get_Child(&dnDevInst,
                      dnParentDevInst,
                      0);
    if (cr != CR_SUCCESS)
        return;

    hDevItem = AddDeviceToTree(hTreeView,
                               hRoot,
                               dnDevInst,
                               bShowHidden);
    if (hDevItem != NULL)
    {
        EnumChildDevices(hTreeView,
                         hDevItem,
                         dnDevInst,
                         bShowHidden);
    }

    while (cr == CR_SUCCESS)
    {
        cr = CM_Get_Sibling(&dnDevInst,
                            dnDevInst,
                            0);
        if (cr != CR_SUCCESS)
            break;

        hDevItem = AddDeviceToTree(hTreeView,
                                   hRoot,
                                   dnDevInst,
                                   bShowHidden);
        if (hDevItem != NULL)
        {
            EnumChildDevices(hTreeView,
                             hDevItem,
                             dnDevInst,
                             bShowHidden);
        }
    }

    (void)TreeView_SortChildren(hTreeView,
                                hRoot,
                                0);
}