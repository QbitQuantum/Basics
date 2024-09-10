void Ctrl::WndFree()
{
	GuiLock __;
	if(!top) return;
	RevokeDragDrop(GetHWND());
	ReleaseUDropTarget(top->dndtgt);
	isopen = false;
	if(!top) return;
	HWND owner = GetWindow(top->hwnd, GW_OWNER);// CXL 31.10.2003 z DoRemove
	bool focus = ::GetFocus() == top->hwnd;
	LLOG("Ctrl::WndDestroy owner " << (void *)owner
	     << " focus " << focus
	     << " ::GetFocus() " << (void *)::GetFocus());
	if(owner && focus) { // CXL 7.11.2003 presun - melo by to fungovat take a neblikat...
		LLOG("Ctrl::WndFree->SetFocus " << UPP::Name(Ctrl::CtrlFromHWND(owner)));
		::SetFocus(owner);
	}
	LLOG(LOG_END << "//Ctrl::WndFree() in " <<UPP::Name(this));
	delete top;
	top = NULL;
}