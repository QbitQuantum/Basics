void CloseRichOwnerCallback(HWND hwnd)
{
	int ind = g_RichEditOwnerList.getIndex((RichEditOwnerData*)&hwnd);
	if (ind == -1)
		return;

	RichEditOwnerData* rdto = g_RichEditOwnerList[ind];
	CloseRichCallback(rdto->hwndInput);
	CloseRichCallback(rdto->hwndLog);
	delete rdto;

	g_RichEditOwnerList.remove(ind);

	mir_unsubclassWindow(hwnd, RichEditOwnerSubclass);
}