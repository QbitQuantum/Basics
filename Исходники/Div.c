__declspec(dllexport) int Div(HWND hWnd,struct TPCLIPINFO *ClipInfo,int Flag,int cnt)
{

	HGLOBAL hRetMem;
	char *buf,*ret;
	char options[256];
	char buffer[256];
	int hSize;

	//データが無い場合は処理を行わない。
	if(ClipInfo == NULL){
		return -1;
	}

	//テキスト以外は処理を行わない。
	if(ClipInfo->Type != CF_TEXT && ClipInfo->Type != CF_OEMTEXT){
		return -1;
	}

	//メモリのサイズを取得する。
	if((hSize = GlobalSize((HGLOBAL)ClipInfo->Mem)) == 0){
		return -1;
	}
	if((buf = GlobalLock((HGLOBAL)ClipInfo->Mem)) == NULL){
		return -1;
	}

	//戻り用のメモリを確保する。
	//とりあえず2倍の量を確保していますが、必要な分で構いません。
	if((hRetMem = GlobalAlloc(GHND,hSize * 2+256)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		return -1;
	}
	if((ret = GlobalLock(hRetMem)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		GlobalFree(hRetMem);
		return -1;
	}




	// **************************************
	// ここで文字列の処理を行います。
	// buf は処理対象の文字列が入ったバッファです。
	// ret は処理後のバッファです。
	// ret に処理を施した文字列を入れて下さい。
	// **************************************
	memset(options,0x00,sizeof(options));
	Dlg(ret,GetForegroundWindow(),"class=?","input class","");
	if(strcmp(ret,"\0")!=0){
		wsprintf(buffer," class=\"%s\"",ret);
		strcat(options,buffer);
	}

	wsprintf(ret,"<div%s>%s</div>",options,buf);

	//処理したバッファのサイズを取得する。
	hSize = lstrlen(ret) + 1;

	GlobalUnlock(hRetMem);
	//再確保を行う。
	if((hRetMem = GlobalReAlloc(hRetMem,hSize,0)) == NULL){
		GlobalUnlock((HGLOBAL)ClipInfo->Mem);
		return -1;
	}

	//元のメモリは解放する。
	GlobalUnlock((HGLOBAL)ClipInfo->Mem);
	GlobalFree(ClipInfo->Mem);

	//構造体に処理をしたメモリのハンドルを設定する。
	ClipInfo->Mem = hRetMem;

	return 0;
}