LRESULT CALLBACK BaseWindow::baseWndProc(HWND hwnd, UINT mess, WPARAM wParam, LPARAM lParam)
{
	BaseWindow *instance = NULL;
	BaseWindow *childInstance = NULL;
	if ( mess == WM_CREATE )
	{
		//ottengo il puntatore this
		CREATESTRUCT *cStruct = (CREATESTRUCT*)lParam;
		instance = (BaseWindow*)cStruct->lpCreateParams;
		if ( instance )
			//salvo il puntatore nello spazio utente della window
			SetWindowLongPtr(hwnd,GWLP_USERDATA, (LONG_PTR)instance);
		return TRUE;
	}
	else
	{
		//verifico la notifica di un child
		if ( mess == NOTIFY_CHILD_CREATION )
		{
			//un child notifica la propria creazione
			HWND tmpHwnd = (HWND)wParam;
			childInstance = (BaseWindow*)lParam;
			if ( childInstance && tmpHwnd )
			{
				//salvo il this sullo spazio utente della hwnd
				SetWindowLongPtr(tmpHwnd, GWLP_USERDATA, (LONG_PTR)childInstance);
			}
		}
		else if ( mess == WM_COMMAND || mess == WM_HSCROLL || mess == WM_VSCROLL )
		{
			instance = BaseWindow::getInstance((HWND)lParam);
		}
		else if ( mess == WM_NOTIFY )
		{
			LPNMHDR data = (LPNMHDR)lParam;
			instance = BaseWindow::getInstance(data->hwndFrom);
		}
		else if ( mess == WM_MENUCOMMAND )
		{
			//messaggio da un menu con MF_BYPOSITION
			HMENU menu = (HMENU)lParam;
			MENUINFO info;
			memset(&info,0,sizeof(MENUINFO));
			info.fMask = MIM_MENUDATA;
			info.cbSize = sizeof(MENUINFO);
			GetMenuInfo(menu,&info);
			instance = (BaseWindow*)info.dwMenuData;
		} 
		/*else if ( mess == WM_CLOSE )
		{
			instance = BaseWindow::getInstance(hwnd);
			if ( instance && instance->closeList ) return instance->closeList->onClose(instance->idWin, instance->getHWND());
			
		} */
		else instance = BaseWindow::getInstance(hwnd); 
		
		if ( instance ) return instance->wndProc(mess, wParam, lParam);
		else return DefWindowProc(hwnd, mess, wParam, lParam);
	
	}
}