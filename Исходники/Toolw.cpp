LRESULT CALLBACK Toolw::tooltipLabelProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT client;
	FwCHAR *tip = NULL;
	CREATESTRUCT *cs;

	switch(message){
		case WM_CREATE:
			Core::self->getToolws()->getToolwset()->add(hDlg);

			cs = (LPCREATESTRUCT)lParam;
			tip = (FwCHAR *)cs->lpCreateParams;

			GetClientRect(hDlg,&client);

			if( tip != NULL ){
				Core::self->CreateWindowExSubstituteFont(
					NULL,
					IDCL_STATIC,
					tip->toWCHAR(),
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					client.left,
					client.top,
					client.right,
					client.bottom,
					hDlg,
					NULL,
					Core::self->getInstance(),
					NULL
					);

				SetWindowPos(hDlg,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				ShowWindow(hDlg,SW_SHOW);
			}
			else {
				DestroyWindow(hDlg);
			}
			break;
		case WM_CTLCOLORSTATIC:
			SetBkMode((HDC)wParam,TRANSPARENT);
			SetDCBrushColor((HDC)wParam,GetSysColor(COLOR_INFOBK));
			SetTextColor((HDC)wParam,GetSysColor(COLOR_INFOTEXT));
			return (LRESULT)GetStockObject(DC_BRUSH);
		case WM_NCACTIVATE:
			return Core::self->getToolws()->overrideNCActivate(hDlg,wParam,lParam);
		case WM_ENABLE:
			return Core::self->getToolws()->overrideEnable(hDlg,wParam,lParam);
		case WM_DESTROY:
			Core::self->getToolws()->getToolwset()->remove(hDlg);
			break;
		default:
			return DefWindowProc(hDlg,message,wParam,lParam);
	}
	return 0;
}