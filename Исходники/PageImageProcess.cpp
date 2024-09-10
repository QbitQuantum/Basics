void CPageImageProcess::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl *pSlider = (CSliderCtrl*)pScrollBar; 
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CCOXRayView *pView = (CCOXRayView *)pFrame->GetActiveView();

	//多个 SLIDER 控件控制 
	switch( pSlider->GetDlgCtrlID() ) 
	{ 
	case IDC_SLIDER_GAMMA:
		{
			m_dbEditGamma = tan(RAD(pSlider->GetPos()));

			m_Gamma.SetGamma(m_dbEditGamma);
			
			if (m_bLBDown)
			{
				::SendMessage(pView->GetSafeHwnd(),WM_GAMMA_CHANGE_PREVIEW,0,0);
			}
			
		}
		
		break;
	} 

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}