const BOOL VentanaDump::Mostrar(const TCHAR *PathDump) { 
	
	
	
	_PathDump = PathDump;
	UINT YC = 6;
	if (Sistema.App.Config.UtilizarBarraTituloWindows == true) { 
		CrearVentana(0, TEXT("BubaTronik_VentanaDump"), WS_OVERLAPPED | WS_SYSMENU, IDIOMA__ERROR_GRAVE, DWL_CENTRADO, DWL_CENTRADO, 547, 150, 0);
		YC = 80;
	}
	else {
		CrearVentana(0, TEXT("BubaTronik_VentanaDump"), WS_POPUP, IDIOMA__ERROR_GRAVE, DWL_CENTRADO, DWL_CENTRADO, 543, 145, 0);
		HRGN Region = CreateRoundRectRgn(0, 0, 544, 146, 11, 11);
		SetWindowRgn(_hWnd, Region, false);
		YC = 100;
	}
	if (_hWnd == NULL) return FALSE;
	_Barra.CrearBarraEx(WS_CHILD | WS_VISIBLE, _hWnd, 10, YC, 522, 8, ID_BARRA_DUMP, DWL_BARRAEX_PROGRESO_HORIZONTAL, 0, 1000);
	_BotonGuardar.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, IDIOMA__ENVIAR, 196, YC + 13, 70, 20, 101);
	_BotonTerminar.CrearBotonEx(WS_CHILD | WS_VISIBLE, _hWnd, IDIOMA__TERMINAR, 276, YC + 13, 70, 20, 100);

	Visible(true);
	_BotonGuardar.AsignarFoco();
	return TRUE;
};