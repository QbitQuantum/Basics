LRESULT VDXVideoFilterDialog::Show(HINSTANCE hInst, LPCSTR templName, HWND parent) {
	if (!hInst)
		hInst = GetLocalHInstance();

	return DialogBoxParamA(hInst, templName, parent, StaticDlgProc, (LPARAM)this);
}