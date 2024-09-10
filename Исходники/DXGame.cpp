void DXGame::drawText(char *text,int x,int y,COLORREF color,LPDDSurface surface){
	HDC xdc; 
	if (FAILED(surface->GetDC(&xdc))){
		dprintf(("DXGame::drawText\n"));
	}
	SetTextColor(xdc, color);
	SetBkMode(xdc, TRANSPARENT_COLOR);
	TextOut(xdc,x,y,text,strlen(text));
	surface->ReleaseDC(xdc);
}	