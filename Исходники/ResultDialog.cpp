// OnSize is a message handler of WM_SIZE messge, 
// it is reimplemented in order to reposition the buttons
// (keep them always in the bottom part of the dialog)
// and resize the rich edit controls as user resized THIS dialog.
void CResultDialog::OnSize(UINT nType, int cx, int cy) 
{ 
  // call the base class handler
  CDialog::OnSize(nType, cx, cy);
  
  //resizes internal GUI controls (rich edit control and 3 buttons)
  //according to given values of this dialog width (cx) and height (cy).
  //the method is called from OnSize message handler and 
  //from InitInstance of OCCDemo to do initial resize
  CWnd *pEd = (CWnd *) GetDlgItem (IDC_RICHEDIT_ResultDialog);
  CWnd *pBCopy = (CWnd *) GetDlgItem (IDC_CopySelectionToClipboard);
  CWnd *pBCopyAll = (CWnd *) GetDlgItem (IDC_CopyAllToClipboard);
  CWnd *pBClose = (CWnd *) GetDlgItem (IDCANCEL);

  if (pEd != NULL) // it is NULL when dialog is being created and OnSize is called
  {
    int butY = cy-bh-d; // y coordinate of buttons' top left corner

    pEd->SetWindowPos(&wndTop, 0, 0, cx, butY-4*d, SWP_NOMOVE);
    pBCopy->SetWindowPos(&wndTop, d, butY, 0, 0, SWP_NOSIZE); 
    pBCopyAll->SetWindowPos(&wndTop, d+bw+d, butY, 0, 0, SWP_NOSIZE);
    pBClose->SetWindowPos(&wndTop, cx-bw-d, butY, 0, 0, SWP_NOSIZE);
  }

  RedrawWindow();
}