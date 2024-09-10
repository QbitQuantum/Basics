// _flags: &1=marker, &2=region
void FillMarkerRegionMenu(ReaProject* _proj, HMENU _menu, int _msgStart, int _flags, UINT _uiState)
{
	int x=0, lastx=0;
	char desc[SNM_MAX_MARKER_NAME_LEN]="";
	while ((x = EnumMarkerRegionDesc(_proj, x, desc, SNM_MAX_MARKER_NAME_LEN, _flags, true, true, true))) {
		if (*desc) AddToMenu(_menu, desc, _msgStart+lastx, -1, false, _uiState);
		lastx=x;
	}
	if (!GetMenuItemCount(_menu))
		AddToMenu(_menu, __LOCALIZE("(No region!)","sws_menu"), 0, -1, false, MF_GRAYED);
}