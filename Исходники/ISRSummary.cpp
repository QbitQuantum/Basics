void CISRSummary::OnLButtonDown(UINT nFlags, CPoint point)
{
    if (m_pPropertySheet) m_pPropertySheet->SetToClose(0);
    CWnd* pWnd;
    if ((pWnd = ChildWindowFromPoint(point,CWP_ALL))!=NULL)
    {
        UINT index = pWnd->GetDlgCtrlID();
        if ((index >= IDC_ISRSUMMARY_FIRST) && (index <= IDC_ISRSUMMARY_LAST))
        {
            if ((index == IDC_ISRSUMMARY_COMMAND6) ||
                    (index == IDC_ISRSUMMARY_COMMAND5) ||
                    (index == IDC_ISRSUMMARY_COMMAND4) ||
                    (index == IDC_ISRSUMMARY_COMMAND3) ||
                    (index == IDC_ISRSUMMARY_COMMAND2) ||
                    (index == IDC_ISRSUMMARY_COMMAND1))
            {
                char Text[256];
                Text[0] = NULL;
                GetDlgItemText(index,Text,sizeof(Text));
                if (strlen(Text))
                {
                    strcat(Text,"\"");
                    memmove(&Text[2],Text,strlen(Text)+1);
                    Text[0] = '"';
                    Text[1] = 'I';
                    _spawnl(_P_NOWAIT,m_pParent->m_szUtilFile,"MsgUtil.exe",Text,NULL);
                }
            }
        }
    }
    CPropertyPage::OnLButtonDown(nFlags, point);
}