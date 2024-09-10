/******************************************************************************
 Function Name  :   OnRButtonDown

 Description    :   The framework calls this member function when the user
                    right clicks on the list box
 Input(s)       :    nFlags -
                    point -
 Output         :   -
 Functionality  :   Shows a popup menu to clear the contents of the listbox
 Member of      :   CNotificListbox

 Author(s)      :   Ravikumar Patil
 Date Created   :   27-03-2003
******************************************************************************/
void CNotificListbox::OnRButtonDown(UINT nFlags, CPoint point)
{
    if (GetCount() > 0)
    {
        CMenu* pomContextMenu = new CMenu;

        if (pomContextMenu != NULL)
        {
            // Load the Menu from the resource
            pomContextMenu->DestroyMenu();
            pomContextMenu->LoadMenu(IDM_OPERATION_LIST);
            CMenu* pomSubMenu = pomContextMenu->GetSubMenu(0);

            if (pomSubMenu != NULL)
            {
                CPoint omSrcPt = point;
                ClientToScreen(&omSrcPt);
                UINT unEnable;

                /* If no item is selected, make "Clear" and "Delete" menu
                items disabled */
                if (GetCurSel() == -1)
                {
                    unEnable = MF_BYCOMMAND | MF_DISABLED | MF_GRAYED;
                }
                else
                {
                    unEnable = MF_BYCOMMAND | MF_ENABLED;
                }

                pomSubMenu->EnableMenuItem(IDM_OPRTN_CLEAR, unEnable);
                pomSubMenu->EnableMenuItem(IDM_OPRTN_DELETE, unEnable);
                pomSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                           omSrcPt.x, omSrcPt.y, this, NULL);
            }

            delete pomContextMenu;
            pomContextMenu = NULL;
        }
    }

    CListBox::OnRButtonDown(nFlags, point);
}