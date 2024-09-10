unsigned long ThreadBuscarArchivos::_ThreadBusqueda(void *pThis) {
    size_t                i    = 0;
    ThreadBuscarArchivos *This = reinterpret_cast<ThreadBuscarArchivos *>(pThis);
	This->_Mutex = CreateMutex(NULL, FALSE, TEXT("Mutex_ThreadBuscarArchivos"));
//    This->_Buscando = true;
	DWL::DWLString *TmpStr = NULL;

    // Inicio la VLC para el analisis
	DWL::DWLString PluginPath;
	PluginPath.sprintf(TEXT("--plugin-path=%s%s"), This->_PathApp(), PATHVLC_PLUGINS);
	ArgumentosVLC ArgsVLC;
	ArgsVLC.AgregarArgumento(This->_PathApp());		// Path de la aplicación
	ArgsVLC.AgregarArgumento(PluginPath());		// Path del directorio de plugins
   	libvlc_instance_t *InstanciaVLC = libvlc_new(ArgsVLC.TotalArgumentos(), ArgsVLC());

	// Inicio el FMOD para el analisis
	FMOD::System *InstanciaFMOD;
	FMOD_RESULT FmodErrorCode = FMOD_OK;
	FmodErrorCode = FMOD::System_Create(&InstanciaFMOD);
	// - Obtengo el path de los pluguins
	DWL::DWLString CodecsPath = This->_PathApp(); CodecsPath += TEXT("Plugins\\FMOD");
	// - Paso el path de unicode a ascii
	char CodecsPathAscii[MAX_PATH + 1] = "";
	WideCharToMultiByte(CP_OEMCP, WC_NO_BEST_FIT_CHARS, CodecsPath(), static_cast<int>(CodecsPath.Tam()) + 1, CodecsPathAscii, MAX_PATH + 1, NULL, NULL);
	FmodErrorCode = InstanciaFMOD->setPluginPath(CodecsPathAscii);
	// Inicio el sonido con 16 canales
	FmodErrorCode = InstanciaFMOD->init(16, FMOD_INIT_NORMAL, NULL);


    // Busco en todas las rutas
	for (i = 0; i < This->_PathsBuscar.size(); i++) This->_BusquedaRecursiva(This->_PathsBuscar[i].Path());

    PostMessage(This->_hWndCP, MENSAJE_OBTENIENDO_DATOS_MEDIOS, static_cast<WPARAM>(This->_PathsEncontrados.size()), NULL);
    // Ya tengo todos los paths, ahora los escaneamos
    InformacionArchivoEx *Info = NULL;
//    libvlc_time_t         TiempoTotal;
//    bool                  EsVideo;
    for (i = 0; i < This->_PathsEncontrados.size(); i++) {        
		if (This->_Mutex) WaitForSingleObject(This->_Mutex, INFINITE);
//		This->_VentanaLog->AgregarMensaje(Log_BubaTronik, Log_Info, "Analizando :", This->_PathsEncontrados[i].Texto());
		if (SendMessage(This->_hWndCP, MENSAJE_MEDIO_NO_EXISTE, reinterpret_cast<WPARAM>(This->_PathsEncontrados[i].Texto()), 0) == 1) {
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(This->_PathsEncontrados[i].Texto()));
			SOLO_DEBUG(DWL::DWLDebug::ImprimirDebug(TEXT("\n")));
			Info = new InformacionArchivoEx;
			TmpStr = new DWL::DWLString(This->_PathsEncontrados[i].Texto());

			PostMessage(This->_hWndCP, MENSAJE_MEDIO_ANALIZANDO, reinterpret_cast<WPARAM>(TmpStr), NULL);

			TMedio *TM = Info->ObtenerInfo(This->_PathsEncontrados[i].Texto(), This->_TipoArchivo, This->_Unidades, This->_PathsBuscar, InstanciaVLC, InstanciaFMOD);
			if (TM != NULL) PostMessage(This->_hWndCP, MENSAJE_MEDIO_ANALIZADO, reinterpret_cast<WPARAM>(TM), NULL);
			else			PostMessage(This->_hWndCP, MENSAJE_MEDIO_INVALIDO, reinterpret_cast<WPARAM>(TM), NULL);
			delete Info;
		}

		if (This->_Cancelar == true) { 
			if (This->_Mutex) ReleaseMutex(This->_Mutex);
			break;
		}
		if (This->_Mutex) ReleaseMutex(This->_Mutex);
    }

//	ReleaseMutex(This->_Mutex);
	// Termino la instancia de la VLC
	libvlc_release(InstanciaVLC);

	// Termino la instancia del FMOD
	InstanciaFMOD->close();
	InstanciaFMOD->release();

	// Cierro el mutex, y informo a la ventana del reproductor que ya se ha terminado
	if (This->_Mutex) CloseHandle(This->_Mutex);
	This->_Mutex = NULL;
    PostMessage(This->_hWndCP, MENSAJE_BUSCAR_ARCHIVOS_TERMINADO, NULL, NULL);
//	MessageBox(NULL, TEXT("Terminado"), TEXT("Terminado"), MB_OK);
    return 0;
}