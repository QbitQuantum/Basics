//////////////////////////////////////////////////////////////////////////////////////////////////
// clipboard
//////////////////////////////////////////////////////////////////////////////////////////////////
void cGUIEdit::ClipboardCopy()
{
	int s1 = sel1(), s2 = sel2();
	int size = s2-s1;
	if(size==0) return; // no selection

	if(!OpenClipboard(NULL)) return;
	if(EmptyClipboard())
	{
		HGLOBAL handler = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE,size+1); assert(handler!=NULL);
		void* data = GlobalLock(handler); assert(data!=NULL);
		memcpy(data,txt.c_str() + s1,size);
		((LPWSTR)data)[size]=0;
		GlobalUnlock(handler);
		SetClipboardData(CF_UNICODETEXT,handler);
	}
	CloseClipboard();
}