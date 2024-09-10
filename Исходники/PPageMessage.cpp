void CPPageMessage::OnItemchangedListMessage(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    // IDE generated code - commented because it isn't needed at present.
    //NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    // If there is a selected item, then it makes sense to keep the "Edit" and
    // "Remove" buttons in enabled state.
    BOOL bToEnable = ((m_odMsgList.GetNextItem(-1, LVNI_SELECTED)) >= 0);

    CButton* pomButton = (CButton*) GetDlgItem(IDC_BUTTON_EDIT);
    if (pomButton != nullptr)
    {
        pomButton->EnableWindow(bToEnable);
    }

    if (m_bForDBMsg == FALSE)
    {
        pomButton = (CButton*) GetDlgItem(IDC_BUTTON_REMOVE);
        if (pomButton != nullptr)
        {
            pomButton->EnableWindow(bToEnable);
        }
    }

    *pResult = 0;
}