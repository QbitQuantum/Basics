// Ends-in Contrast Stretching의 최저값 설정
void CBMPFrame::OnIpEcsLowEnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCRibbonEdit *pSpin = DYNAMIC_DOWNCAST(CMFCRibbonEdit,
		((CMainFrame*)GetTopLevelFrame())->GetRibbonBar()->FindByID(ID_IP_ECSLOW));
	m_bEcsLowEnd = (BYTE)_wtof(pSpin->GetEditText());
}