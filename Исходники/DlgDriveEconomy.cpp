void CDlgDriveEconomy::OnLButtonUp(UINT nFlags, CPoint point) 
{
	for(int i=0;i<enCtrCount;i++)
	{
		if(m_Item[i].nState==BTN_STATE_DOWN)
		{
			m_Item[i].nState = BTN_STATE_NORMAL;
			
			switch( i )
			{
			case 0:
				{
				}
				break;
			case 1:
				{
					CDlgOilConsum dlg;
					dlg.DoModal();
				}
				break;
			case 2:
				{
					CDlgDriveEconomySetting dlg;
					dlg.DoModal();
				}
				break;
			case 3: 
				OnExit();
				break;
			default:
				break;
			}
		}
	}
	
	Invalidate();
	ReleaseCapture();
	CDialogBase::OnLButtonUp(nFlags, point);
}