INT_PTR ResizeDialog(WPARAM, LPARAM lParam)
{
	UTILRESIZEDIALOG *urd=(UTILRESIZEDIALOG*)lParam;
	HDWP hDwp;
	int i;
	DLGITEMTEMPLATE *pItem = NULL;
	START_OF_DLGITEMTEMPLATEEX *pItemEx = NULL;
	RECT rc;
	PWORD pWord;
	DLGTEMPLATE *pTemplate;
	START_OF_DLGTEMPLATEEX *pTemplateEx;
	UTILRESIZECONTROL urc;
	int procResult;
	int extendedDlg,itemCount;

	if(urd==NULL||urd->cbSize!=sizeof(UTILRESIZEDIALOG)) return 1;
	pTemplate=(DLGTEMPLATE*)LockResource(LoadResource(urd->hInstance,FindResourceA(urd->hInstance,urd->lpTemplate,MAKEINTRESOURCEA(5))));
	pTemplateEx=(START_OF_DLGTEMPLATEEX*)pTemplate;
	extendedDlg=pTemplateEx->signature==0xFFFF;
	if(extendedDlg && pTemplateEx->dlgVer!=1)
		return 1;

	if(extendedDlg) pWord=(PWORD)(pTemplateEx+1);
	else pWord=(PWORD)(pTemplate+1);
	if(*pWord==0xFFFF) pWord+=2; else while(*pWord++);   //menu
	if(*pWord==0xFFFF) pWord+=2; else while(*pWord++);   //class
	while(*pWord++);   //title
	if(extendedDlg) {
		if(pTemplateEx->style&DS_SETFONT) {
			pWord+=3;    //font size,weight,italic
			while(*pWord++);   //font name
		}
	}
	else {
		if(pTemplate->style&DS_SETFONT) {
			pWord++;    //font size
			while(*pWord++);   //font name
		}
	}

	urc.cbSize=sizeof(UTILRESIZECONTROL);
	rc.left=0; rc.top=0;
	if(extendedDlg) {rc.right=pTemplateEx->cx; rc.bottom=pTemplateEx->cy;}
	else {rc.right=pTemplate->cx; rc.bottom=pTemplate->cy;}
	MapDialogRect(urd->hwndDlg,&rc);
	urc.dlgOriginalSize.cx=rc.right; urc.dlgOriginalSize.cy=rc.bottom;
	GetClientRect(urd->hwndDlg,&rc);
	urc.dlgNewSize.cx=rc.right; urc.dlgNewSize.cy=rc.bottom;

	if(extendedDlg) itemCount=pTemplateEx->cDlgItems;
	else itemCount=pTemplate->cdit;
	hDwp=BeginDeferWindowPos(itemCount);
	for(i=0;i<itemCount;i++) {
		if((UINT_PTR)pWord&2) pWord++;       //dword align

		if(extendedDlg) {
			pItemEx=(START_OF_DLGITEMTEMPLATEEX*)pWord;
			pWord=(PWORD)(pItemEx+1);

			urc.wId=pItemEx->id;
			urc.rcItem.left=pItemEx->x; urc.rcItem.top=pItemEx->y;
			urc.rcItem.right=urc.rcItem.left+pItemEx->cx; urc.rcItem.bottom=urc.rcItem.top+pItemEx->cy;
		}
		else {
			pItem=(DLGITEMTEMPLATE*)pWord;
			pWord=(PWORD)(pItem+1);

			urc.wId=pItem->id;
			urc.rcItem.left=pItem->x; urc.rcItem.top=pItem->y;
			urc.rcItem.right=urc.rcItem.left+pItem->cx; urc.rcItem.bottom=urc.rcItem.top+pItem->cy;
		}
		if(*pWord==0xFFFF) pWord+=2; else while(*pWord++);   //menu
		if(*pWord==0xFFFF) pWord+=2; else while(*pWord++);   //class
		pWord+=1+(1+*pWord)/2;     //creation data

		if(urc.wId==65535) continue;  //using this breaks the dwp, so just ignore it

		MapDialogRect(urd->hwndDlg,&urc.rcItem);
		procResult=(urd->pfnResizer)(urd->hwndDlg,urd->lParam,&urc);
		if(procResult&RD_ANCHORX_RIGHT) {
			urc.rcItem.left+=urc.dlgNewSize.cx-urc.dlgOriginalSize.cx;
			urc.rcItem.right+=urc.dlgNewSize.cx-urc.dlgOriginalSize.cx;
		}
		else if(procResult&RD_ANCHORX_WIDTH)
			urc.rcItem.right+=urc.dlgNewSize.cx-urc.dlgOriginalSize.cx;
		else if(procResult&RD_ANCHORX_CENTRE) {
			urc.rcItem.left+=(urc.dlgNewSize.cx-urc.dlgOriginalSize.cx)/2;
			urc.rcItem.right+=(urc.dlgNewSize.cx-urc.dlgOriginalSize.cx)/2;
		}
		if(procResult&RD_ANCHORY_BOTTOM) {
			urc.rcItem.top+=urc.dlgNewSize.cy-urc.dlgOriginalSize.cy;
			urc.rcItem.bottom+=urc.dlgNewSize.cy-urc.dlgOriginalSize.cy;
		}
		else if(procResult&RD_ANCHORY_HEIGHT)
			urc.rcItem.bottom+=urc.dlgNewSize.cy-urc.dlgOriginalSize.cy;
		else if(procResult&RD_ANCHORY_CENTRE) {
			urc.rcItem.top+=(urc.dlgNewSize.cy-urc.dlgOriginalSize.cy)/2;
			urc.rcItem.bottom+=(urc.dlgNewSize.cy-urc.dlgOriginalSize.cy)/2;
		}
		hDwp = DeferWindowPos(hDwp,GetDlgItem(urd->hwndDlg,extendedDlg?pItemEx->id:pItem->id),0,urc.rcItem.left,urc.rcItem.top,urc.rcItem.right-urc.rcItem.left,urc.rcItem.bottom-urc.rcItem.top,SWP_NOZORDER);
	}
	EndDeferWindowPos(hDwp);
	return 0;
}