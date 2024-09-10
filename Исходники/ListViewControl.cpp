void ListViewControl::RedrawHeader()
{
	HWND hHeader = (HWND)SendMessage(getHandle(), LVM_GETHEADER, 0, 0);
	RedrawWindow(hHeader, NULL, NULL, RDW_INVALIDATE);
}