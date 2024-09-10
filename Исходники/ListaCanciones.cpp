void ListaCanciones::ActualizarTodo(const bool nRepintar) {
	// Calculamos los anchos necesarios para las columnas
	_Ver_HorasMinutosSegundos = false;
	_Ver_DigitosPista = 2;

	ItemListaMedios *aItem  = NULL;
	int              aPista = 0;
	for (size_t i = 0; i < _ListaEx_Items.size(); i++) {
		aItem = static_cast<ItemListaMedios *>(_ListaEx_Items[i]);
		switch (aItem->Medio->TipoMedio) {
			case Tipo_Medio_Audio :
				aPista = static_cast<TMedioAudio *>(aItem->Medio)->Pista;
				break;
			case Tipo_Medio_CDAudio :
				aPista = static_cast<TMedioCDAudio *>(aItem->Medio)->Pista;
				break;
			case Tipo_Medio_Video :
				aPista = static_cast<TMedioVideo *>(aItem->Medio)->Pista;
				break;
		}
		// Miro si la pista tiene 4 digitos
		if (aPista > 999) _Ver_DigitosPista = 4;
		if (aPista > 99 && _Ver_DigitosPista == 2) _Ver_DigitosPista = 3;
		// Miro si el tiempo llega a una hora
		if (static_cast<int>(((aItem->Medio->Tiempo / 1000) / 60) / 60) > 0) _Ver_HorasMinutosSegundos = true;
	}

	// Reasigno el ancho de las columnas
	RECT RC;
	GetClientRect(_hWnd, &RC);
	_ListaEx_Columnas[0]->Ancho(_Ver_DigitosPista * 10, false);
	if (_Ver_HorasMinutosSegundos == true) {
		_ListaEx_Columnas[1]->Ancho((RC.right - 36) - ((_Ver_DigitosPista * 10) + 51) , false);
		_ListaEx_Columnas[2]->Ancho(51, false);
	}
	else { // 36 = 18 icono + 18 scroll
		_ListaEx_Columnas[1]->Ancho((RC.right - 36) - ((_Ver_DigitosPista * 10) + 35) , false);
		_ListaEx_Columnas[2]->Ancho(35, false);
	}

	// Asignamos los textos de la lista correctamente
	DWL::DWLString PistaFinal;
	DWL::DWLString TiempoFinal;
	for (size_t i = 0; i < _ListaEx_Items.size(); i++) {
		aItem = static_cast<ItemListaMedios *>(_ListaEx_Items[i]);
		switch (aItem->Medio->TipoMedio) {
			case Tipo_Medio_Audio :
				aPista = static_cast<TMedioAudio *>(aItem->Medio)->Pista;
				break;
			case Tipo_Medio_CDAudio :
				aPista = static_cast<TMedioCDAudio *>(aItem->Medio)->Pista;
				break;
			case Tipo_Medio_Video :
				aPista = static_cast<TMedioVideo *>(aItem->Medio)->Pista;
				break;
		}
		if		(_Ver_DigitosPista == 4) PistaFinal.sprintf(TEXT("%04d"), aPista);
		else if (_Ver_DigitosPista == 3) PistaFinal.sprintf(TEXT("%03d"), aPista);
		else if (_Ver_DigitosPista == 2) PistaFinal.sprintf(TEXT("%02d"), aPista);
		_ListaEx_Items[i]->Texto(0, PistaFinal(), false);
		
		if (_Ver_HorasMinutosSegundos == true)	TiempoFinal = Sistema.App.Media.TiempoStrL(aItem->Medio->Tiempo);
		else									TiempoFinal = Sistema.App.Media.TiempoStr(aItem->Medio->Tiempo);
		_ListaEx_Items[i]->Texto(2, TiempoFinal(), false);
	}

	DWL::ControlesEx::DWLListaEx::ActualizarTodo(nRepintar);
}