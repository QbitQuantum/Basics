void CConfigureDialog::ShowChild(int number)
{
	AtlTrace("Showing tab %d\n", number);

	// Validate the parameter
	if ((number >= 0) && (number < numTabs))
	{
		// Hide every window except for the chosen one
		for (int count = 0; count < numTabs; count++)
		{
			if (count != number)
			{
				dialogs[count]->ShowWindow(SW_HIDE);
			}
			else if (count == number)
			{
#ifdef notdef
				// Show the chosen window and set it's location
				dialogs[count]->SetWindowPos(&wndTop, m_rSettingsRect.left,
					m_rSettingsRect.top, m_rSettingsRect.right,
					m_rSettingsRect.bottom, SWP_SHOWWINDOW);
#endif
				// Show the chosen window and set it's location
				dialogs[count]->ShowWindow(SW_SHOW);


				// Select tab zero
				SendDlgItemMessage(IDC_TAB, TCM_SETCURSEL, (WPARAM)number, 0);
			}
		}
	}
}