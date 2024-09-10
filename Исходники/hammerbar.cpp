//-----------------------------------------------------------------------------
// Purpose: adds controls to the CHammerBar
//			determines position and stretch settings based on default design /			
// Input  : int nIDTemplate - ID from .rc file of control to be added
//			DWORD dwPlacementFlag - placement information
//				GROUP_BOX - will be stretched to fit new size
//				BOTTOM_JUSTIFY - will move with the bottom of the dialog	
//				RIGHT_JUSTIFY - will move with the right side of the dialog//			
// Output : void
//-----------------------------------------------------------------------------
void CHammerBar::AddControl( int nIDTemplate, DWORD dwPlacementFlag )
{
	ControlInfo_t newControl;
	newControl.m_nIDDialogItem = nIDTemplate;
	newControl.m_dwPlacementFlag = dwPlacementFlag;

	CWnd *pControl = GetDlgItem( nIDTemplate );
	if ( pControl != NULL )
	{
		CRect controlPos, hammerBarPos;
		pControl->GetWindowRect( &controlPos );
		GetWindowRect( &hammerBarPos );

		newControl.m_nHeightBuffer	= m_sizeDefault.cy - controlPos.Height(); 
		newControl.m_nWidthBuffer	= m_sizeDefault.cx - controlPos.Width();
		newControl.m_nPosX			= m_sizeDefault.cx + hammerBarPos.left - controlPos.left;
		newControl.m_nPosY			= m_sizeDefault.cy + hammerBarPos.top - controlPos.top;
		
		m_ControlList.AddToTail( newControl );
	}
}