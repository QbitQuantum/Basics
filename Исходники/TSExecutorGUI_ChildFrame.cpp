/******************************************************************************
Function Name  :  OnClose
Input(s)       :
Output         :  void
Functionality  :
Member of      :  CTSExecutorChildFrame
Friend of      :  -
Author(s)      :  Venkatanarayana Makam
Date Created   :  28/04/2011
Modifications  :
Code Tag       :
******************************************************************************/
void CTSExecutorChildFrame::OnClose()
{
    WINDOWPLACEMENT wndPlcmnt;

    GetWindowPlacement(&wndPlcmnt);

    wndPlcmnt.showCmd = SW_HIDE;

    SetWindowPlacement(&wndPlcmnt);
    CWnd* pActivateWnd =   GetNextWindow();
    pActivateWnd->SetForegroundWindow();
    pActivateWnd->SetFocus();
    ShowWindow(SW_HIDE);
}