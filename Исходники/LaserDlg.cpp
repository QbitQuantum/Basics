/*雷射歸零*/
void CLaserDlg::OnBnClickedBtnzero()
{
	((CCommandTestDlg*)pMain)->a.m_Action.LA_SetZero();
    ((CCommandTestDlg*)pMain)->HeightLaserZero = ((CCommandTestDlg*)pMain)->a.m_Action.g_HeightLaserZero;
    ((CCommandTestDlg*)pMain)->LaserOffsetz = ((CCommandTestDlg*)pMain)->a.m_Action.g_OffSetLaserZ;
    CString StrBuff,StrBuff1;
    GetDlgItemTextW(IDC_STALASERTOTIP, StrBuff);
    StrBuff1.Format(_T(",%d,%d"), ((CCommandTestDlg*)pMain)->HeightLaserZero, ((CCommandTestDlg*)pMain)->LaserOffsetz);
    StrBuff = StrBuff + StrBuff1;
    SetDlgItemText(IDC_STALASERTOTIP, StrBuff);
}