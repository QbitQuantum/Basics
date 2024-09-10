/**
* \author	Darryn Campbell (DCC, JRQ768)
* \date		October 2009
*/
LRESULT CIEBrowserEngine::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = S_OK;

    switch (uMsg) 
	{
		case WM_NOTIFY:
		{
			//  Received a message from the Pocket Internet Explorer component
			//  to indicate something has happened (BeforeNavigate / DocumentComplete etc).
			//  The lParam contains an NM_HTMLVIEWW containing information about
			//  the event, parse it.
			NM_HTMLVIEWW * pnmHTML;
			LPNMHDR pnmh;
			pnmHTML = (NM_HTMLVIEWW *) lParam;
			pnmh    = (LPNMHDR) &(pnmHTML->hdr);
			
			//  The message has originated from one of the tabs we created, determine
			//  the tab ID from the hwnd
			//IETab* tab = GetSpecificTab(hwndParentOfOriginator);
            CIEBrowserEngine* mobileTab = CIEBrowserEngine::getInstance();

			//  Invoke the appropriate tab with the event.  The data will vary
			//  depending on which event has been received
			TCHAR tcTarget[MAX_URL + 1];
			memset (tcTarget, 0, sizeof(TCHAR) * MAX_URL + 1);
			switch (pnmh->code)
			{
			case NM_PIE_TITLE:
				//  The Page Title has been received from the Page, convert 
				//  the content to a wide string
				if (pnmHTML->szTarget)
					mbstowcs(tcTarget, (LPSTR)pnmHTML->szTarget, MAX_URL);
				if (tcTarget)
					mobileTab->InvokeEngineEventTitleChange(tcTarget);
				break;
			case NM_PIE_META:

				//  A Meta Tag has been received from the Page, convert the content
				//  and data to wide strings.
				if (pnmHTML->szTarget)
					mbstowcs(tcTarget, (LPSTR)pnmHTML->szTarget, MAX_URL);
				TCHAR tcData[MAX_URL+1];
				memset(tcData, 0, sizeof(TCHAR) * MAX_URL + 1);
				if (pnmHTML->szData)
					mbstowcs(tcData, (LPSTR)pnmHTML->szData, MAX_URL);
				//  If there is both an HTTP Equiv and some Content to the Meta
				//  tag then invoke it
				if (tcTarget && tcData)
					mobileTab->InvokeEngineEventMetaTag(tcTarget, tcData);			
				break;
			case NM_PIE_BEFORENAVIGATE:
				if (pnmHTML->szTarget)
					mbstowcs(tcTarget, (LPSTR)pnmHTML->szTarget, MAX_URL);

				// GD - stop navigation if target starts with file:// and ends with '\'.
				// This is the generated target when using <a href=""> from a local page.
				// If we don't stop it then the File Explorer is launched.
				if (wcslen (tcTarget) >= 8)
					if (!wcsnicmp (tcTarget, L"file://", 7))
						if (tcTarget [wcslen (tcTarget) - 1] == '\\')
						{
							LOG(TRACE) + "Navigation to file folder aborted\n";
							return S_FALSE;
						}
				if (tcTarget)
					mobileTab->InvokeEngineEventLoad(tcTarget, EEID_BEFORENAVIGATE);
				break;
			case NM_PIE_DOCUMENTCOMPLETE:
				if (pnmHTML->szTarget)
					mbstowcs(tcTarget, (LPSTR)pnmHTML->szTarget, MAX_URL);
				//  If the network is available but the server being reached
				//  is inaccessible the browser component appears to immediately
				//  give a document complete with the current page URL (not the
				//  page being navigated to) which is hiding the hourglass, 
				//  stop this behaviour.
				if (tcTarget && !wcsicmp(tcTarget, mobileTab->m_tcNavigatedURL))
					mobileTab->InvokeEngineEventLoad(tcTarget, EEID_DOCUMENTCOMPLETE);
				break;
			case NM_PIE_NAVIGATECOMPLETE:
				if (pnmHTML->szTarget)
					mbstowcs(tcTarget, (LPSTR)pnmHTML->szTarget, MAX_URL);
				if (tcTarget)
					mobileTab->InvokeEngineEventLoad(tcTarget, EEID_NAVIGATECOMPLETE);
				break;
			case NM_PIE_KEYSTATE:
			case NM_PIE_ALPHAKEYSTATE:
				//  Not Used
				break;

			}
		}	

		lResult = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return lResult;
}