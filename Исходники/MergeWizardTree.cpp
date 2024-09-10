BOOL CMergeWizardTree::OnInitDialog()
{
    CMergeWizardBasePage::OnInitDialog();

    CMergeWizard * pWizard = (CMergeWizard*)GetParent();
    CString sUUID = pWizard->sUUID;
    m_URLCombo.SetURLHistory(true, false);
    m_URLCombo.LoadHistory(L"Software\\TortoiseSVN\\History\\repoURLS\\"+sUUID, L"url");
    m_URLCombo2.SetURLHistory(true, false);
    m_URLCombo2.LoadHistory(L"Software\\TortoiseSVN\\History\\repoURLS\\"+sUUID, L"url");
    m_URLCombo2.SetCurSel(0);

    CString sRegKeyFrom = L"Software\\TortoiseSVN\\History\\repoURLS\\MergeURLForFrom" + ((CMergeWizard*)GetParent())->wcPath.GetSVNPathString();
    CString sMergeUrlForWCFrom = CRegString(sRegKeyFrom);
    CString sRegKeyTo = L"Software\\TortoiseSVN\\History\\repoURLS\\MergeURLForTo" + ((CMergeWizard*)GetParent())->wcPath.GetSVNPathString();
    CString sMergeUrlForWCTo = CRegString(sRegKeyTo);

    if (!(DWORD)CRegDWORD(L"Software\\TortoiseSVN\\MergeWCURL", FALSE))
        m_URLCombo.SetCurSel(0);
    else
    {
        if (!sMergeUrlForWCFrom.IsEmpty())
            m_URLCombo.SetWindowText(CPathUtils::PathUnescape(sMergeUrlForWCFrom));
        if (!sMergeUrlForWCTo.IsEmpty())
            m_URLCombo2.SetWindowText(CPathUtils::PathUnescape(sMergeUrlForWCTo));
    }
    // Only set the "From" Url if there is no url history available
    if (m_URLCombo.GetString().IsEmpty())
        m_URLCombo.SetWindowText(CPathUtils::PathUnescape(pWizard->url));
    GetDlgItem(IDC_BROWSE)->EnableWindow(!m_URLCombo.GetString().IsEmpty());
    if (m_URLCombo2.GetString().IsEmpty())
        m_URLCombo2.SetWindowText(CPathUtils::PathUnescape(pWizard->url));
    if (!pWizard->URL1.IsEmpty())
        m_URLCombo.SetWindowText(CPathUtils::PathUnescape(pWizard->URL1));
    if (!pWizard->URL2.IsEmpty())
        m_URLCombo2.SetWindowText(CPathUtils::PathUnescape(pWizard->URL2));
    GetDlgItem(IDC_BROWSE2)->EnableWindow(!m_URLCombo2.GetString().IsEmpty());

    SetDlgItemText(IDC_WCEDIT, ((CMergeWizard*)GetParent())->wcPath.GetWinPath());

    // set head revision as default revision
    if (pWizard->startRev.IsHead() || !pWizard->startRev.IsValid())
        CheckRadioButton(IDC_REVISION_HEAD1, IDC_REVISION_N1, IDC_REVISION_HEAD1);
    else
    {
        CheckRadioButton(IDC_REVISION_HEAD1, IDC_REVISION_N1, IDC_REVISION_N1);
        m_sStartRev = pWizard->startRev.ToString();
        SetDlgItemText(IDC_REVISION_START, m_sStartRev);
    }
    if (pWizard->endRev.IsHead() || !pWizard->endRev.IsValid())
        CheckRadioButton(IDC_REVISION_HEAD, IDC_REVISION_N, IDC_REVISION_HEAD);
    else
    {
        CheckRadioButton(IDC_REVISION_HEAD, IDC_REVISION_N, IDC_REVISION_N);
        m_sEndRev = pWizard->endRev.ToString();
        SetDlgItemText(IDC_REVISION_END, m_sEndRev);
    }

    AdjustControlSize(IDC_REVISION_HEAD1);
    AdjustControlSize(IDC_REVISION_N1);
    AdjustControlSize(IDC_REVISION_HEAD);
    AdjustControlSize(IDC_REVISION_N);

    AddAnchor(IDC_MERGETREEFROMGROUP, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_URLCOMBO, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_BROWSE, TOP_RIGHT);
    AddAnchor(IDC_REVISION_HEAD1, TOP_LEFT);
    AddAnchor(IDC_REVISION_N1, TOP_LEFT);
    AddAnchor(IDC_REVISION_START, TOP_LEFT);
    AddAnchor(IDC_FINDBRANCHSTART, TOP_LEFT);
    AddAnchor(IDC_MERGETREETOGROUP, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_URLCOMBO2, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_BROWSE2, TOP_RIGHT);
    AddAnchor(IDC_REVISION_HEAD, TOP_LEFT);
    AddAnchor(IDC_REVISION_N, TOP_LEFT);
    AddAnchor(IDC_REVISION_END, TOP_LEFT);
    AddAnchor(IDC_FINDBRANCHEND, TOP_LEFT);
    AddAnchor(IDC_MERGETREEWCGROUP, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_WCEDIT, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_SHOWLOGWC, TOP_RIGHT);

    StartWCCheckThread(((CMergeWizard*)GetParent())->wcPath);

    return TRUE;
}