/** @brief user pressed <enter> key. */
void CTestFilterDlg::OnOK()
{
   CWnd *pWnd = GetFocus(); 
   ASSERT (pWnd); 
   if (IDCANCEL == pWnd->GetDlgCtrlID()) 
   { 
       CDialog::OnCancel(); 
   }
   else
   {
	   OnTestBtn();
   }
}