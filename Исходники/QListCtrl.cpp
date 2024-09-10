void CQListCtrl::OnTimer(UINT_PTR nIDEvent) 
{
	//http://support.microsoft.com/kb/200054
	//OnTimer() Is Not Called Repeatedly for a List Control
	bool callBase = true;

	switch(nIDEvent)
	{
		case TIMER_SHOW_PROPERTIES:
			{
				if( theApp.m_bShowingQuickPaste )
					ShowFullDescription(true);
				KillTimer(TIMER_SHOW_PROPERTIES);

				callBase = false;
			}
			break;

		case TIMER_HIDE_SCROL:
			{
				CPoint cursorPos;
				GetCursorPos(&cursorPos);

				CRect crWindow;
				this->GetWindowRect(&crWindow);

				

				//check and see if they moved out of the scroll area
				//If they did tell our parent so
				if(MouseInScrollBarArea(crWindow, cursorPos) == false)
				{
					StopHideScrollBarTimer();
				}

				callBase = false;
			}
			break;

		case TIMER_SHOW_SCROLL:
			{
				CPoint cursorPos;
				GetCursorPos(&cursorPos);

				CRect crWindow;
				this->GetWindowRect(&crWindow);

				//Adjust for the v-scroll bar being off of the screen
				crWindow.right -= theApp.m_metrics.ScaleX(GetSystemMetrics(SM_CXVSCROLL));
				crWindow.bottom -= theApp.m_metrics.ScaleX(::GetSystemMetrics(SM_CXHSCROLL));

				//Check and see if we are still in the cursor area
				if(MouseInScrollBarArea(crWindow, cursorPos))
				{
					m_timerToHideScrollAreaSet = true;
					GetParent()->SendMessage(NM_SHOW_HIDE_SCROLLBARS, 1, 0);

					//Start looking to hide the scroll bars
					SetTimer(TIMER_HIDE_SCROL, 1000, NULL);
				}

				KillTimer(TIMER_SHOW_SCROLL);

				callBase = false;
			}
			break;
	}
	
	if(callBase)
	{
		CListCtrl::OnTimer(nIDEvent);
	}
}