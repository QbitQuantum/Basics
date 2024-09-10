void DeleteState(HWND hWnd) {
	DialogData *d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYUP), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYDOWN), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYLEFT), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYRIGHT), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYA), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYB), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYX), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYY), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYL), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYR), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYSELECT), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYSTART), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYNEXTSTATE), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYPREVSTATE), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYSAVESTATE), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYLOADSTATE), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;
	GetWindowSubclass(GetDlgItem(hWnd, IDC_IEKEYFASTFORWARD), InternalEmulatorInputDialogProc, NULL, (DWORD_PTR *)(&d));
	delete d;

}