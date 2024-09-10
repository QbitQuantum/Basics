/******************************************************************************
 Function Name  :   OnRButtonDown

 Description    :   The framework calls this member function when the user
                    right clicks on the list box
 Input(s)       :   nFlags -
                    point -
 Output         :   -
 Functionality  :   Shows a popup menu to remove an entry or to clear entries
 Member of      :   CSignalWatchListBox

 Author(s)      :   Ratnadip Choudhury, Amarnath Shastri
 Date Created   :   03-04-2002
 Modified by    :   Ratnadip Choudhury
 Modified on    :   26-04-2002
 Modified by    :   Raja N
 Modified on    :   22.07.2004, Modified the function call to refer ListCtrl
******************************************************************************/
void CSignalWatchListBox::OnRButtonDown(UINT nFlags, CPoint omPoint)
{
    if (GetItemCount() > 0)
    {
        CMenu* pomContextMenu = new CMenu;
        if (pomContextMenu != NULL)
        {
            // Load the Menu from the resource
            pomContextMenu->DestroyMenu();
            pomContextMenu->LoadMenu(IDM_MENU_SIGNAL_WATCH);
            CMenu* pomSubMenu = pomContextMenu->GetSubMenu(1);

            if (pomSubMenu != NULL)
            {
                CPoint omSrcPt = omPoint;
                ClientToScreen(&omSrcPt);
                UINT unEnable;
                // If no item is selected, make "Delete" menu item disabled
                if (GetSelectedCount() == -1)
                {
                    unEnable = MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
                }
                else
                {
                    unEnable = MF_BYCOMMAND | MF_ENABLED;
                }
                pomSubMenu->EnableMenuItem(IDM_SG_WATCH_CLEAR, unEnable);
                pomSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                           omSrcPt.x, omSrcPt.y, this, NULL);
            }
            delete pomContextMenu;
            pomContextMenu = NULL;
        }
    }

    CFFListCtrl::OnRButtonDown(nFlags, omPoint);
}