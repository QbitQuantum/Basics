LRESULT CALLBACK CContainer::TabBackingProc(HWND hTabCtrl,
UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITMENU:
			SendMessage(m_hContainer,WM_INITMENU,wParam,lParam);
			break;

		case WM_MEASUREITEM:
			{
				MEASUREITEMSTRUCT	*pMeasureItem = NULL;

				pMeasureItem = (MEASUREITEMSTRUCT *)lParam;

				pMeasureItem->itemWidth = 20;
				pMeasureItem->itemHeight = 10;

			}
			break;

		case WM_LBUTTONDBLCLK:
			{
				HRESULT hr;

				hr = BrowseFolder(m_DefaultTabDirectory,SBSP_ABSOLUTE,TRUE,TRUE,FALSE);

				if(FAILED(hr))
					BrowseFolder(m_DefaultTabDirectoryStatic,SBSP_ABSOLUTE,TRUE,TRUE,FALSE);
			}
			break;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case TABTOOLBAR_CLOSE:
					OnCloseTab();
					break;
			}
			break;

		case WM_NOTIFY:
			switch(((LPNMHDR)lParam)->code)
			{
				case TCN_SELCHANGE:
					OnTabSelectionChange();
					break;

				case TTN_GETDISPINFO:
					OnTabCtrlGetDispInfo(lParam);
					break;
			}
			break;
	}

	return DefSubclassProc(hTabCtrl,msg,wParam,lParam);
}