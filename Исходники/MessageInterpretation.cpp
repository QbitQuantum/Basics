/******************************************************************************
 Function Name  :   vResizeControls

 Description    :
 Input(s)       :   -
 Output         :   -
 Functionality  :   Resize the control when dialog is resized.
 Member of      :   CMessageInterpretation

 Author(s)      :   Ratnadip Choudhury
 Date Created   :   16.02.2004
 Modifications  :   Raja N on 05/04/2004
                :   Modified width calculation as one more column is included
                    in the list.
******************************************************************************/
void CMessageInterpretation::vResizeControls(void)
{
    RECT WndClientRect, CtrlRect;
    CStatic* pomStatic = nullptr;

    GetClientRect(&WndClientRect);

    /* Resize "Message" static control */
    if ((pomStatic = (CStatic*) GetDlgItem(IDC_CAPTION)) != nullptr)
    {
        pomStatic->GetWindowRect(&CtrlRect);
        ScreenToClient(&CtrlRect);
        pomStatic->MoveWindow(CtrlRect.left, CtrlRect.top,
                              WndClientRect.right - WndClientRect.left,
                              CtrlRect.bottom - CtrlRect.top);
    }

    /* Resize "Signal" static control */
    if ((pomStatic = (CStatic*) GetDlgItem(IDC_CAPTION2)) != nullptr)
    {
        pomStatic->GetWindowRect(&CtrlRect);
        ScreenToClient(&CtrlRect);
        pomStatic->MoveWindow(CtrlRect.left, CtrlRect.top,
                              WndClientRect.right - WndClientRect.left,
                              CtrlRect.bottom - CtrlRect.top);
    }

    /* Resize list control describing signal values */
    if (IsWindow(m_ctrlSignal.m_hWnd))
    {
        m_ctrlSignal.GetWindowRect(&CtrlRect);
        ScreenToClient(&CtrlRect);
        m_ctrlSignal.MoveWindow(5, CtrlRect.top,
                                WndClientRect.right - WndClientRect.left - 10,
                                WndClientRect.bottom - CtrlRect.top - 5);

        m_ctrlSignal.GetWindowRect(&CtrlRect);
        // Get the column width
        int nWidth = (CtrlRect.right - CtrlRect.left - 20) / 4;
        m_ctrlSignal.SetColumnWidth(0, nWidth);
        m_ctrlSignal.SetColumnWidth(1, nWidth);
		m_ctrlSignal.SetColumnWidth(2, nWidth);
		m_ctrlSignal.SetColumnWidth(3, nWidth);
    }
}