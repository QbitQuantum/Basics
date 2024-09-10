/******************************************************************************
Function Name  :  OnNMRclick
Input(s)       :
Output         :  void
Functionality  :
Member of      :  CTreeViewEx
Friend of      :  -
Author(s)      :  Venkatanarayana Makam
Date Created   :  30/03/2011
Modifications  :
******************************************************************************/
void CTreeViewEx::OnNMRclick(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    // TODO: Add your control notification handler code here
    CPoint point;
    GetCursorPos(&point);
    CPoint omCurrentPoint(point);
    ScreenToClient(&omCurrentPoint);
    UINT flags;
    HTREEITEM hItem = GetTreeCtrl().HitTest(omCurrentPoint, &flags);
    CTreeCtrl& omTempTreeCtrl = GetTreeCtrl();
    if(hItem && (flags & TVHT_ONITEM) && !(flags & TVHT_ONITEMRIGHT))
    {
        omTempTreeCtrl.SelectItem(hItem);
        eTYPE_ENTITY eEnityType = GetEditorWindow()->eGetCurrentEntityType();
        CMenu omContextMenu;

        VERIFY(omContextMenu.CreatePopupMenu());
        if(eEnityType == TEST_SETUP)
        {
            VERIFY(omContextMenu.AppendMenu(MF_STRING, IDM_ADD_TESTCASE, _("New Test Case")));
        }
        else if(eEnityType == TEST_CASE)
        {
            CMenu omSubMenu;
            omSubMenu.CreatePopupMenu();
            omSubMenu.AppendMenu(MF_STRING, IDM_ADD_SEND, _("Send"));
            omSubMenu.AppendMenu(MF_STRING, IDM_ADD_VERIFY, _("Verify"));
            omSubMenu.AppendMenu(MF_STRING, IDM_ADD_WAIT, _("Wait"));
            omSubMenu.AppendMenu(MF_STRING, IDM_ADD_VERIFYRESPONSE, _("verfiyResponse"));
            omSubMenu.AppendMenu(MF_STRING, IDM_ADD_VERIFYDLC, _("verifyDlc"));
            //omSubMenu.AppendMenu(MF_STRING, IDM_ADD_REPLAY, _T("Replay"));
            omContextMenu.AppendMenu(MF_POPUP, (UINT_PTR)omSubMenu.m_hMenu, _("New"));
            omContextMenu.AppendMenu(MF_STRING, IDM_DELETE, _("Delete"));
        }
        else
        {
            omContextMenu.AppendMenu(MF_STRING, IDM_DELETE, _("Delete"));
        }

        if(omContextMenu.GetMenuItemCount() > 0)
        {
            omContextMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
        }
        *pResult = 0;
    }

    else        //On Tree View Create Collapse All and Expand All
    {
        CMenu omContextMenu;
        VERIFY(omContextMenu.CreatePopupMenu());
        VERIFY(omContextMenu.AppendMenu(MF_STRING, IDM_COLLAPSE_ALL, _("Collapse All")));
        VERIFY(omContextMenu.AppendMenu(MF_STRING, IDM_EXPAND_ALL, _("Expand All")));
        VERIFY(omContextMenu.AppendMenu(MF_SEPARATOR));
        VERIFY(omContextMenu.AppendMenu(MF_STRING, IDM_SETTINGS_CLR, _("Background Color")));
        omContextMenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
        *pResult = 0;
    }
}