static void TextProcessor(INT hdlImage,CHAR *lpText)
{
	BYTE *lp;
	CHAR szTesto[1024];
	POINT pt;
	IMGHEADER *Img;
	HDC hDC,hDClone;
	HBITMAP hbCopy;
	BYTE *lpSorg;
	INT iLx,iLy;
	BITMAPINFOHEADER *BmpHeader;
	BITMAPINFO *BmpInfo;
	INT iAlt=12;
	INT iCol1=0;
	INT iCol2=-1;
	BOOL fBold=FALSE;

	// ----------------------------------------------------------------------------
	// Creo una zona di memoria tipo video delle dimensioni dell'immagine
	//
	//memcpy(&ImgHeader,memoLock(hdlImage),sizeof(IMGHEADER));
	printf("Elaborazione TextProcessor [%s]" CRLF,lpText); //Sleep(2000);
	//ehLogWrite("> %s" CRLF,lpText);
	if (!*lpText) return;

	Img=memoLock(hdlImage);
	BmpInfo=(BITMAPINFO *) &Img->bmiHeader;
	BmpHeader=(BITMAPINFOHEADER *) &Img->bmiHeader;
    iLy=BmpHeader->biHeight; if (iLy<0) iLy=-BmpHeader->biHeight;
    iLx=BmpHeader->biWidth;

    hDC=GetDC(NULL); hDClone=CreateCompatibleDC(hDC); 
	SetMapMode(hDClone, MM_TEXT);
	hbCopy = CreateCompatibleBitmap(hDC, iLx, iLy);
	SelectObject(hDClone, hbCopy);
	ReleaseDC(NULL,hDC);

    lpSorg=(BYTE *) Img;  lpSorg+=Img->Offset;

	// Scrivo l'immagine in questa zona di memoria
	if (StretchDIBits(hDClone, 
					  // Coordinate e dimensioni di stampa a video
					  0,0,
					  iLx, 
					  iLy,

					  // Coordinate e dimensioni di lettura nel sorgente
					  0,
					  iLy+1,
					  iLx,
					  -iLy,
					  lpSorg,
					  (BITMAPINFO *) &Img->bmiHeader,
					  DIB_RGB_COLORS, 
					  SRCCOPY) == GDI_ERROR) {printf("StretchDIBits Failed");}

	// Ci faccio quello che ci devo fare con i comandi
	lp=strtok(lpText,"|");
	*szTesto=0;
	ZeroFill(pt);
	while (lp)
	{
		//printf("[%s]" CRLF,lp); 

		if (!memcmp(lp,"TEXT=",5)) strcpy(szTesto,lp+5);
		if (!memcmp(lp,"PX=",3)) pt.x=atoi(lp+3);
		if (!memcmp(lp,"PY=",3)) pt.y=atoi(lp+3);
		if (!memcmp(lp,"ALT=",3)) iAlt=atoi(lp+3);
		if (!memcmp(lp,"COL=",4)) iCol1=ColorConvert(lp+4);
		if (!memcmp(lp,"BG=",3)) iCol2=ColorConvert(lp+3);
		if (!memcmp(lp,"BOLD=",5)) fBold=atoi(lp+5);
		
		if (*lp=='*') 
		{
			//printf("Stampo: %d,%d,%s" CRLF,pt.x,pt.y,szTesto);
			//ehLogWrite("Stampo: %d,%d,%s",pt.x,pt.y,szTesto);
			LPrint(hDClone,pt.x,pt.y,iCol1,iCol2,"Arial",iAlt,fBold,szTesto);
		}

		lp=strtok(NULL,"|");
	}

	// Mi riprendo la zona di memoria video e la rimetto nell'immagine
	//BmpHeader->biHeight*=-1;
	GetDIBits(
		hDClone,           // handle to device context
		hbCopy,      // handle to bitmap
		0,   // first scan line to set in destination bitmap
		iLy,   // number of scan lines to copy
		lpSorg,    // address of array for bitmap bits
		(BITMAPINFO *) &Img->bmiHeader, // address of structure with bitmap data
		DIB_RGB_COLORS        // RGB or palette index
		);
	
	if (!DeleteDC(hDClone)) 
	{
		ehLogWrite("Errore in cancellazione DC %d",GetLastError());
		ehExit("Errore in cancellazione DC");
	}

	if (!DeleteObject(hbCopy))
	{
		ehLogWrite("Errore in cancellazione Bitmap %d",GetLastError());
		ehExit("Errore in cancellazione Bitmap");
	}

	memoUnlockEx(hdlImage,"A5");
	IMGMirrorY(hdlImage);
	
	// Libero le risorse

	//TextOut(


}