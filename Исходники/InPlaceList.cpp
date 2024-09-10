CInPlaceList::CInPlaceList(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
                           int nRow, int nColumn,
                           Strings& Items,
                           CString sInitText,
                           UINT nFirstChar)
{
    m_nNumLines = 2;
    m_sInitText = sInitText;
    m_nRow		= nRow;
    m_nCol      = nColumn;
    m_nLastChar = 0;
    m_bEdit = FALSE;

    // Create the combobox
    DWORD dwComboStyle = WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|
                         CBS_AUTOHSCROLL | dwStyle;

    if (!Create(dwComboStyle, rect, pParent, nID))
        return;

    COMBOBOXINFO cbInfo;
    cbInfo.cbSize = sizeof(COMBOBOXINFO);
    GetComboBoxInfo(&cbInfo);

    m_edit.SubclassWindow(cbInfo.hwndItem);
    m_ListBox.SubclassWindow(cbInfo.hwndList);

    // Add the strings
    for (size_t i = 0; i < Items.size(); i++)
        AddString(Items[i]);

    // Get the maximum width of the text strings
    int nMaxLength = 0;
    CClientDC dc(GetParent());
    CFont* pOldFont = dc.SelectObject(pParent->GetFont());

    for (size_t i = 0; i < Items.size(); i++)
        nMaxLength = max(nMaxLength, dc.GetTextExtent(Items[i]).cx);

    nMaxLength += (::GetSystemMetrics(SM_CXVSCROLL) + dc.GetTextExtent(_T(" ")).cx*2);
    dc.SelectObject(pOldFont);

    // Resize the edit window and the drop down window

    SetFont(pParent->GetFont());

    SetDroppedWidth(nMaxLength);
    SetHorizontalExtent(0); // no horz scrolling

    // Set the initial text to m_sInitText
    SetWindowText(m_sInitText);		// No text selected, so restore what was there before
    ShowDropDown();

    SetFocus();

    // Added by KiteFly. When entering DBCS chars into cells the first char was being lost
    // SenMessage changed to PostMessage (John Lagerquist)
    switch (nFirstChar)
    {
    case VK_RETURN:
        break;

    default:
        PostMessage(WM_CHAR, nFirstChar);
    }
}