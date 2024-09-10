void CSettingDlg::OnSelchangeCbSize()
{
    CString strTemp;
    m_cbResolution.GetLBText(m_cbResolution.GetCurSel(), strTemp);
    swscanf_s(strTemp.GetBuffer(), _T("%dx%d"), &m_nWidth, &m_nHeight);

    UpdateData(FALSE);
    GetDlgItem(IDC_APPLY)->EnableWindow(TRUE);
}