// Modifie la transparence
void SetTransparency( HWND hwnd, int value ) {
#ifndef NO_TRANSPARENCY
	SetLayeredWindowAttributes( hwnd, 0, value, LWA_ALPHA ) ;
#endif
	}