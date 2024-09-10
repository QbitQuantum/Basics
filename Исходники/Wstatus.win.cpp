Wstatus::Wstatus(string name, Wform * parent){

	this->name = name;
	HWND hWnd = parent->gethandle();
	hSW = CreateStatusWindow(WS_CHILD | WS_VISIBLE, NULL, hWnd, wId);
	setparent(parent);

}