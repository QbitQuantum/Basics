unsigned long BuscarActualizaciones::ThreadBuscarActualizacion(void *phWnd) {
//	try {
		HINTERNET		Sesion				= InternetOpen(TEXT("BubaTronik"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
		HINTERNET		Peticion			= InternetOpenUrl(Sesion, TEXT("http://www.devildrey33.es/BubaTronik/VERSION_BUBATRONIK.txt"), NULL, 0, INTERNET_FLAG_RELOAD, 0);
		char			Txt[32]				= "";
		DWORD			BytesLeidos			= 0;
		DWORD			TotalBytesLeidos	= 0;
		DWORD			MaxBuffer			= sizeof(Txt) -1;
		DWL::DWLString	Ret;
		// No se ha encontrado la version :/
		if (Peticion == NULL) {
    		InternetCloseHandle(Sesion);
			return 0;
		}

		BOOL Leido = InternetReadFile(Peticion, Txt, MaxBuffer, &BytesLeidos);
		if (BytesLeidos != 0) {
			Txt[BytesLeidos] = 0;
			Ret += Txt;
	//		ZeroMemory(Txt, sizeof(Txt) * sizeof(char));
		}
		HWND hWndPlayer = reinterpret_cast<HWND>(phWnd);

		if (Ret.Tam() == 0)	{
			InternetCloseHandle(Peticion);
			InternetCloseHandle(Sesion);
			return 0; 
		}
		if (Ret[0] == TEXT('<')) {
			InternetCloseHandle(Peticion);
			InternetCloseHandle(Sesion);
			return 0; // no se ha encontrado el documento
		}
		DWL::DWLString Version;
		Version.sprintf(TEXT("%.02f"), static_cast<float>(APP_NUM_VER));
		// La versión no es la misma, leemos las novedades
		if (Ret.SubStr(0, Version.Tam()) != Version)	{
    	
    		HINTERNET PeticionNovedades	= InternetOpenUrl(Sesion, TEXT("http://www.devildrey33.es/BubaTronik/NOVEDADES_BUBATRONIK.txt"), NULL, 0, INTERNET_FLAG_RELOAD, 0);
			DWORD	  TotalDatos        = 0;
    		DWORD	  Descargado		= 64;
			TCHAR	  TotalDatosStr[64];
			BOOL bRet = HttpQueryInfo(PeticionNovedades, HTTP_QUERY_CONTENT_LENGTH, (LPVOID)TotalDatosStr, &Descargado, (LPDWORD)0);
			if (bRet == TRUE) TotalDatos = _wtol(TotalDatosStr);
			char     *TmpBuffer = new char[TotalDatos + 1];

    		Leido = InternetReadFile(PeticionNovedades, TmpBuffer, TotalDatos, &BytesLeidos);
    		if (BytesLeidos != 0 && BytesLeidos <= TotalDatos) TmpBuffer[BytesLeidos] = 0;
			Sistema.App.PlayerEx.VentanaActualizacion.Novedades(TmpBuffer);
			delete [] TmpBuffer;

			PostMessage(hWndPlayer, MENSAJE_ACTUALIZACION_ENCONTRADA, 0, 0);
		}
		InternetCloseHandle(Peticion);
		InternetCloseHandle(Sesion);
//	}
//	catch (...) {
//	}
	return 0;
}