int static OnIconLibIconChanged(WPARAM wParam,LPARAM lParam)
{
	HICON hicon;
	CLISTMENUITEM clmi={0};
	BOOL needFree;
    if (MirandaExiting()) return 0;
	hicon=CLUI_LoadIconFromExternalFile("clisticons.dll",2,TRUE,FALSE,"NewGroup","Contact List","New Group",-IDI_NEWGROUP2,&needFree);
	NewGroupIconidx=ImageList_ReplaceIcon(hCListImages,NewGroupIconidx,hicon);	
	if (needFree) DestroyIcon_protect(hicon);
	clmi.cbSize=sizeof(clmi);
	clmi.flags=CMIM_ICON;
	clmi.hIcon=ske_ImageList_GetIcon(hCListImages,NewGroupIconidx,0);
	CallService(MS_CLIST_MODIFYMENUITEM,(WPARAM)hNewSubGroupMenuItem,(LPARAM)&clmi);
	CallService(MS_CLIST_MODIFYMENUITEM,(WPARAM)hNewGroupMenuItem,(LPARAM)&clmi);
	//
	

	return 0;
};