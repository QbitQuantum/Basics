void *ClientData::run()
{
	USHORT sz,fr;

	if(type==ClientData::t_send)
	{
		// Send on the socket the datas shared

		// Send the format of the clipboard data
		char info[sizeof(USHORT)*2];
		sz=htons(*size);
		fr=htons(*format);
		memcpy(info,&sz,sizeof(USHORT));
		memcpy(info+sizeof(USHORT),&fr,sizeof(USHORT));

		// Send the data
		int result=send(s,info,sizeof(USHORT)*2,NULL);

		if(result==0	|| result==SOCKET_ERROR)
		{
			//printError(L"send");
			//MessageBox(hWnd,_T("Invio dei dati preliminari fallito"),_T("Errore"),MB_OK);
			return NULL;
		}

		result=send(s,data,*size,NULL);

		if(result==0	|| result==SOCKET_ERROR)
		{
			//printError(L"send");
			//MessageBox(hWnd,_T("Invio dei dati fallito"),_T("Errore"),MB_OK);
			return NULL;
		}

	}else{

		// Connect with the owner of the clipboard required

		sockaddr_in c_in;
		int addr_sz=sizeof(c_in);
		
		SOCKET s_tmp=accept(s,reinterpret_cast<sockaddr *>(&c_in),&addr_sz);
		if(s_tmp==INVALID_SOCKET)
		{
			//printError(L"accept");
			MessageBox(hWnd,_T("Nessuna risposta dal proprietario; trasferimento della clipboard fallito."),_T("Errore"),MB_OK);
			return NULL;
		}

		closesocket(s);
		s=s_tmp;

	
		// Receive the size and format of the clipboard data
		char info[sizeof(USHORT)*2];
		if(!recv_timeout(s,info,sizeof(USHORT)*2,0))
		{
			//MessageBox(hWnd,_T("Nessun dato preliminare dal client!"),_T("Errore"),MB_OK);
			MessageBox(hWnd,_T("Nessuna risposta dal proprietario; trasferimento della clipboard fallito."),_T("Errore"),MB_OK);
			return NULL;
		}

		memcpy(&sz,info,sizeof(USHORT));
		memcpy(&fr,info+sizeof(USHORT),sizeof(USHORT));
		sz=htons(sz);
		fr=htons(fr);

		// Receive the data
		if(sz<1)
		{
			MessageBox(hWnd,_T("Ricevuto un valore di size inaccettabile; trasferimento della clipboard fallito."),_T("Errore"),MB_OK);
			return NULL;
		}

		char *cbData=new char[sz];

		if(!recv_timeout(s,cbData,sz,0))
		{
			//printError(L"recv_timeout");
			MessageBox(hWnd,_T("Nessuna risposta dal proprietario; trasferimento della clipboard fallito."),_T("Errore"),MB_OK);	
			return NULL;
		}

		// Copy datas in the clipboard
		if(OpenClipboard(hWnd)==false)
		{
			//printError(L"OpenClipboard");
			MessageBox(hWnd,L"Impossibile accedere alla Clipboard; trasferimento della clipboard fallito.",_T("Errore"),MB_OK);
			delete[] cbData;
			return false;
		}

		if(EmptyClipboard()==false)
		{
			//printError(L"EmptyClipboard");
			MessageBox(hWnd,L"Impossibile svuotare la clipboard; trasferimento della clipboard fallito.",_T("Errore"),MB_OK);
			delete[] cbData;
			CloseClipboard();
			return false;
		}

		HANDLE hData=GlobalAlloc(GMEM_MOVEABLE, sz); 
        if (hData == NULL) 
        { 
            //printError(L"GlobalAlloc");
			MessageBox(hWnd,L"Impossibile allocare l'oggetto globale; trasferimento della clipboard fallito.",_T("Errore"),MB_OK);
			delete[] cbData;
			CloseClipboard();
			return false;
		}
 
        // Lock the handle and copy the text to the buffer. 
        LPVOID lptstrCopy = GlobalLock(hData); 
        memcpy(lptstrCopy, cbData, sz);
        GlobalUnlock(hData); 

        // Place the handle on the clipboard. 
		if(SetClipboardData(fr,hData)==NULL)
		{
			//printError(L"SetClipboardData");
			MessageBox(hWnd,L"Impossibile impostare i dati nella clipboard.",_T("Errore"),MB_OK);
			GlobalFree(hData);
			delete[] cbData;
			return false;
		}

		if(CloseClipboard()==false)
		{
			printError(L"CloseClipboard");
			MessageBox(hWnd,L"Impossibile chiudere la Clipboard.",_T("Errore"),MB_OK);
			return false;
		}
		MessageBox(hWnd,_T("I dati richiesti sono stati trasferiti nella tua clipboard."),_T("Avviso"),MB_OK);
	}

	return NULL;
}