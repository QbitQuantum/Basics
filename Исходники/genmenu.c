//wparam=0
//lparam=LPDRAWITEMSTRUCT
int MO_DrawMenuItem(WPARAM wParam,LPARAM lParam)
{
	PMO_IntMenuItem pimi=NULL;
	int y,objidx,menuitemidx;
	LPDRAWITEMSTRUCT dis=(LPDRAWITEMSTRUCT)lParam;

	if (!isGenMenuInited) return -1;

	if (dis==NULL){return(FALSE);}

	lockmo();

	if (GetAllIdx(dis->itemData,&objidx,&menuitemidx)==0){unlockmo();return(FALSE);}
	pimi=&MenuObjects[objidx].MenuItems[menuitemidx];

	if (pimi==NULL||pimi->iconId==-1) {unlockmo();return (FALSE);}

	y=(dis->rcItem.bottom-dis->rcItem.top-GetSystemMetrics(SM_CYSMICON))/2+1;
	if (dis->itemState&ODS_SELECTED)	{
		if (dis->itemState&ODS_CHECKED) {
			RECT rc;
			rc.left=2; rc.right=GetSystemMetrics(SM_CXSMICON)+2;
			rc.top=y; rc.bottom=rc.top+GetSystemMetrics(SM_CYSMICON)+2;
			FillRect(dis->hDC,&rc,GetSysColorBrush(COLOR_HIGHLIGHT));
			ImageList_DrawEx(MenuObjects[objidx].hMenuIcons,pimi->iconId,dis->hDC,2,y,0,0,CLR_NONE,CLR_DEFAULT,ILD_SELECTED);
		}
		else
			ImageList_DrawEx(MenuObjects[objidx].hMenuIcons,pimi->iconId,dis->hDC,2,y,0,0,CLR_NONE,CLR_DEFAULT,ILD_FOCUS);
		//DrawIconEx(dis->hDC,2,y,pimi->iconId,16,16,0,0,DI_NORMAL);
	}
	else {
		if (dis->itemState&ODS_CHECKED) {
			HBRUSH hBrush;
			RECT rc;
			COLORREF menuCol,hiliteCol;
			rc.left=0; rc.right=GetSystemMetrics(SM_CXSMICON)+4;
			rc.top=y-2; rc.bottom=rc.top+GetSystemMetrics(SM_CYSMICON)+4;
			DrawEdge(dis->hDC,&rc,BDR_SUNKENOUTER,BF_RECT);
			InflateRect(&rc,-1,-1);
			menuCol=GetSysColor(COLOR_MENU);
			hiliteCol=GetSysColor(COLOR_3DHIGHLIGHT);
			hBrush=CreateSolidBrush(RGB((GetRValue(menuCol)+GetRValue(hiliteCol))/2,(GetGValue(menuCol)+GetGValue(hiliteCol))/2,(GetBValue(menuCol)+GetBValue(hiliteCol))/2));
			FillRect(dis->hDC,&rc,GetSysColorBrush(COLOR_MENU));
			DeleteObject(hBrush);
			ImageList_DrawEx(MenuObjects[objidx].hMenuIcons,pimi->iconId,dis->hDC,2,y,0,0,CLR_NONE,GetSysColor(COLOR_MENU),ILD_BLEND50);
		}
		else
			ImageList_DrawEx(MenuObjects[objidx].hMenuIcons,pimi->iconId,dis->hDC,2,y,0,0,CLR_NONE,CLR_NONE,ILD_NORMAL);
		//DrawIconEx(dis->hDC,2,y,pimi->iconId,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0,0,DI_NORMAL);
	}
	unlockmo();
	return TRUE;
}