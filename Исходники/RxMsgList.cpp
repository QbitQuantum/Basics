/*******************************************************************************
  Function Name  : OnContextMenu
  Input(s)       : pWnd, point
  Output         : -
  Functionality  : Show the context menu with a list of column names as menu items.
  Member of      : CRxMsgList
  Author(s)      : Arunkumar K
  Date Created   : 20-05-2010
  Modifications  : 
*******************************************************************************/
void CRxMsgList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{	
	if (point.x==-1 && point.y==-1)
	{
		// OBS! point is initialized to (-1,-1) if using SHIFT+F10 or VK_APPS		
	}
	else
	{
		CPoint pt = point;
		ScreenToClient(&pt);

		CRect headerRect;
		GetHeaderCtrl()->GetClientRect(&headerRect);
		if (headerRect.PtInRect(pt))
		{
			// Show context-menu with the option to show hide columns
			CMenu menu;
			if (menu.CreatePopupMenu())
			{
				for( int i = GetColumnStateCount()-1 ; i >= 0; --i)
				{
					UINT uFlags = MF_BYPOSITION | MF_STRING;

					// Put check-box on context-menu
					if (IsColumnVisible(i))
						uFlags |= MF_CHECKED;
					else
						uFlags |= MF_UNCHECKED;

					if(i == 0)		//Disable 'Time' column
						break;

					// Retrieve column-title
					LVCOLUMN lvc = {0};
					lvc.mask = LVCF_TEXT;
					TCHAR sColText[256];
					lvc.pszText = sColText;
				
					lvc.cchTextMax = 15;	//Set the Width of Menu Items here
					//lvc.cchTextMax = sizeof(sColText)-1;
					VERIFY( GetColumn(i, &lvc) );

					menu.InsertMenu(0, uFlags, i, lvc.pszText);					
				}

				menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, 0);
			}
		}
	}
}