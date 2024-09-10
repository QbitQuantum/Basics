// Here you can process the Npp Messages 
// I will make the messages accessible little by little, according to the need of plugin development.
// Please let me know if you need to access to some messages :
// http://sourceforge.net/forum/forum.php?forum_id=482781
//
extern "C" __declspec(dllexport) LRESULT messageProc(UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message){
		case WM_CREATE:
		hInst = GetModuleHandle(NULL);

		//Create PopupMenu Dynamically
		HGLOBAL hgbl;
		LPDLGTEMPLATE lpdt;
		LPWORD lpw;
		hwndEdit = nppData._scintillaMainHandle;
		hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);

		lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);

		// Define a dialog box.

		lpdt->style = WS_POPUP | WS_BORDER ;
		lpdt->cdit = 0;         // Number of controls = 0
		lpdt->x  = 10;  lpdt->y  = 10;
		lpdt->cx = 100; lpdt->cy = 100;

		lpw = (LPWORD)(lpdt + 1);
		*lpw++ = 0;             // No menu
		*lpw++ = 0;             // Predefined dialog box class (by default)

		GlobalUnlock(hgbl);
		hwndPopupMenu = CreateDialogIndirect(hInst,
			(LPDLGTEMPLATE)hgbl,
			nppData._nppHandle,
			(DLGPROC)PopupMenuProc);
		GlobalFree(hgbl);
		
		//End PopupMenuDialog

		hfontCurrent = MyCreateFont(nppData._nppHandle, 10,L"Zawgyi-One");
		EditProc =(WNDPROC)GetWindowLongW(nppData._scintillaMainHandle, GWL_WNDPROC);
		SetWindowLong(nppData._scintillaMainHandle, GWL_WNDPROC, (long)SubEditProc);
		hMenu = GetMenu(nppData._nppHandle);
		CheckMenuItem(hMenu,funcItem[1]._cmdID,MF_BYCOMMAND|MF_CHECKED);//Check Disable Menu
		break;
		case WM_MOVE:
			//move menu along with the main window
			if(IsWindowVisible(hwndPopupMenu))
			{
				RECT rctWinMain;
				GetWindowRect(hwndEdit,&rctWinMain);

				int height=(burmese.menuLength>MROW?10:burmese.menuLength)*MHEIGHT+MHEIGHT+10;
				int width=((burmese.menuLength/MROW)+1)*MWIDTH;

				MoveWindow (hwndPopupMenu,
					rctWinMain.left + pointEditCursor.x + 10,
					rctWinMain.top + pointEditCursor.y + 20 ,
					width,
					height,
					TRUE) ;
			}
	        
			break;
		}
	return true;
}