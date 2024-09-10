void CPathDialog::InitDialogBar()
{
	CW3ZMapEditApp *pTheApp = (CW3ZMapEditApp *)AfxGetApp();
	ASSERT_VALID(pTheApp);
	m_iPenSize = pTheApp->m_ToolPathEdit.GetToolSize();
	UpdateData(FALSE);

	m_btnNoWalk.SetTriState(TRUE);
	m_btnNoWalk.SetTextOnly(TRUE);
	m_btnNoWalk.SetWindowText(STR_PATH_NOWALK);
	m_btnNoWalk.SetState(EB_STATE0);
	m_btnNoWalk.SetColorState2(0x0000C000);

	m_btnNoBuild.SetTriState(TRUE);
	m_btnNoBuild.SetTextOnly(TRUE);
	m_btnNoBuild.SetState(EB_STATE0);
	m_btnNoBuild.SetColorState2(0x0000C000);

	m_btnNoFly.SetTriState(TRUE);
	m_btnNoFly.SetTextOnly(TRUE);
	m_btnNoFly.SetState(EB_STATE0);
	m_btnNoFly.SetColorState2(0x0000C000);

	m_btnBlight.SetTriState(TRUE);
	m_btnBlight.SetTextOnly(TRUE);
	m_btnBlight.SetState(EB_STATE0);
	m_btnBlight.SetColorState2(0x0000C000);

	m_btnNoWater.SetTriState(TRUE);
	m_btnNoWater.SetTextOnly(TRUE);
	m_btnNoWater.SetState(EB_STATE0);
	m_btnNoWater.SetColorState2(0x0000C000);

	m_btnUnknown.SetTriState(TRUE);
	m_btnUnknown.SetTextOnly(TRUE);
	m_btnUnknown.SetState(EB_STATE0);
	m_btnUnknown.SetColorState2(0x0000C000);

	m_btnUnkn01.SetTriState(TRUE);
	m_btnUnkn01.SetTextOnly(TRUE);
	m_btnUnkn01.SetState(EB_STATE0);
	m_btnUnkn01.SetColorState2(0x0000C000);

	m_btnUnkn02.SetTriState(TRUE);
	m_btnUnkn02.SetTextOnly(TRUE);
	m_btnUnkn02.SetState(EB_STATE0);
	m_btnUnkn02.SetColorState2(0x0000C000);

	UpdateColors();
	UpdateCurrentColor();
}