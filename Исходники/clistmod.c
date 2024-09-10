int CListIconsChanged(WPARAM wParam,LPARAM lParam)
{
	int i,j;

	for(i=0;i<sizeof(statusModeList)/sizeof(statusModeList[0]);i++)
		ImageList_ReplaceIcon(hCListImages,i+1,LoadSkinnedIcon(skinIconStatusList[i]));
	ImageList_ReplaceIcon(hCListImages,IMAGE_GROUPOPEN, LoadSkinnedIcon(SKINICON_OTHER_GROUPOPEN));
	ImageList_ReplaceIcon(hCListImages,IMAGE_GROUPSHUT, LoadSkinnedIcon(SKINICON_OTHER_GROUPSHUT));
	for(i=0;i<protoIconIndexCount;i++)
		for(j=0;j<sizeof(statusModeList)/sizeof(statusModeList[0]);j++)
			ImageList_ReplaceIcon(hCListImages,protoIconIndex[i].iIconBase+j,LoadSkinnedProtoIcon(protoIconIndex[i].szProto,statusModeList[j]));
	TrayIconIconsChanged();
	InvalidateRectZ((HWND)CallService(MS_CLUI_GETHWND,0,0),NULL,TRUE);
	return 0;
}