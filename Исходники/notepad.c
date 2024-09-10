void Notepad_OnDropFiles(HWND hwnd, HDROP hDropInfo, char * filename ) {
	int nb, taille ;
	nb=DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0 );
	if( nb> 0 ) {
		taille=DragQueryFile(hDropInfo, 0, NULL, 0 )+1;
		DragQueryFile(hDropInfo, 0, filename, taille );
		}
	DragFinish(hDropInfo);
	}