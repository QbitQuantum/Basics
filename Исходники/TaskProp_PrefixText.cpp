void CTaskProp_PrefixText::OnChangeEditTaskItemPrefixText()
{
    CWnd* pWnd = GetDlgItem(IDC_CHECK_TASK_POST_PREFIX_TEXT);
    if(pWnd->GetWindowTextLength() == 0)
        pWnd->EnableWindow(FALSE);
    else
        pWnd->EnableWindow(TRUE);

}