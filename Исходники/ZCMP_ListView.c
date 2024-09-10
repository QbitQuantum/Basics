// -----------------------------------------------
// List view di lettura (senza sort header)
// -----------------------------------------------
void * ehzListView(struct OBJ *objCalled,EN_MESSAGE cmd,LONG info,void *ptr)
{
	EH_DISPEXT *psExt=ptr;
	static SINT HdbMovi=-1;
	static INT16 iSend;
	DWORD dwExStyle;
	SINT iLVIndex;

	if (fReset)
	{
		if (cmd!=WS_START) win_infoarg("Inizializzare ehzListView()");
		memset(&_arsLv,0,sizeof(EH_LVLIST)*LVMAX);
		EhListInizialize();
		fReset=FALSE;
		return 0;
	}

	iLVIndex=LVFind(LV_FINDOBJ,objCalled);
	if (iLVIndex<0) iLVIndex=LVAlloc(objCalled);

 switch(cmd)
	{
		case WS_INF:
			return &_arsLv[iLVIndex];
 
		case WS_OPEN: // Creazione
			
			objCalled->hWnd=CreateListView(objCalled->nome,sys.EhWinInstance,WindowNow());
			_arsLv[iLVIndex].hWndList=objCalled->hWnd;
			_arsLv[iLVIndex].hWndHeader=ListView_GetHeader(objCalled->hWnd);//GetWindow(objCalled->hWnd, GW_CHILD);
			_arsLv[iLVIndex].idHeader=GetDlgCtrlID(_arsLv[iLVIndex].hWndHeader);
			_arsLv[iLVIndex].fLeftClick=TRUE;
			_arsLv[iLVIndex].fRightClick=TRUE;
			_arsLv[iLVIndex].fDoubleClick=FALSE;
			break;

		case WS_EXTNOTIFY:
			switch (info)
			{
				case 0: _arsLv[iLVIndex].subListNotify=ptr; break;
				case 1: _arsLv[iLVIndex].subMessage=ptr; break;
				case 2: _arsLv[iLVIndex].subHeaderNotify=ptr; break;
			}				
			break;

		case WS_SETFLAG:

			if (!strcmp(ptr,"STYLE")) // Setta lo stile della finestra
			{
				DWORD dwStyle;
				dwStyle=GetWindowLong(objCalled->hWnd, GWL_STYLE);
				dwStyle|=info;
				SetWindowLong(objCalled->hWnd, GWL_STYLE, (DWORD) dwStyle);
			}

			if (!strcmp(ptr,"!STYLE")) // Setta lo stile della finestra
			{
				LONG lStyle;
				lStyle=GetWindowLong(objCalled->hWnd, GWL_STYLE);
				lStyle&=~info;
				SetWindowLong(objCalled->hWnd, GWL_STYLE, lStyle);
			}

			if (!strcmp(ptr,"STYLEMASK")) // Setta lo stile della finestra
			{
				DWORD dwStyle;
				dwStyle=GetWindowLong(objCalled->hWnd, GWL_STYLE);
				//win_infoarg("%08x",~LVS_TYPESTYLEMASK);
				dwStyle=dwStyle&~LVS_TYPESTYLEMASK|info;
				SetWindowLong(objCalled->hWnd, GWL_STYLE, (DWORD) dwStyle);
			}

			if (!strcmp(ptr,"EXSTYLE")) // Setta lo stile della finestra
			{
				dwExStyle=ListView_GetExtendedListViewStyle(objCalled->hWnd);
				dwExStyle|=info;
				ListView_SetExtendedListViewStyle(objCalled->hWnd,dwExStyle);
			}

			if (!strcmp(ptr,"!EXSTYLE")) // Setta lo stile della finestra
			{
				dwExStyle=ListView_GetExtendedListViewStyle(objCalled->hWnd);
				dwExStyle&=~info;
				ListView_SetExtendedListViewStyle(objCalled->hWnd,dwExStyle);
			}

			if (!strcmp(ptr,"DCLK")) // Setta il Double Click
			{
				_arsLv[iLVIndex].fDoubleClick=info;
			}
			break;

		case WS_CLOSE: // Distruzione
			DestroyWindow(objCalled->hWnd);
			break;

		case WS_DEL: // Cancella le colonne
			while (TRUE)
			{
				if (!ListView_DeleteColumn(objCalled->hWnd,0)) break;
			}
    		break;

		case WS_ADD: // Aggiungi una colonna
			ListView_InsertColumn(objCalled->hWnd, info, (LV_COLUMN *) ptr);
			break;

		case WS_LINK: // Aggiunge un Item
			//
			if (ListView_SetItem(objCalled->hWnd,(LPLVITEM) ptr)==FALSE) 
				{ListView_InsertItem(objCalled->hWnd,(LPLVITEM) ptr);}
			break;

		case WS_DO: // Spostamento / Ridimensionamento
			MoveWindow(objCalled->hWnd,psExt->px,psExt->py,psExt->lx,psExt->ly,TRUE);
			break;

		case WS_DISPLAY: 
			InvalidateRect(objCalled->hWnd,NULL,TRUE);
			break;
	}
	return NULL;
}