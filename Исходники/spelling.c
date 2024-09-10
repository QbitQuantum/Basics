static void _clearSuggestions(HWND hwnd){
	int				count = SendDlgItemMessageW(hwnd, IDC_LST_MISPRINTS, LB_GETCOUNT, 0, 0);

	for(int i = 0; i < count; i++){
		PSUGGESTION		ps = (PSUGGESTION)SendDlgItemMessageW(hwnd, IDC_LST_MISPRINTS, LB_GETITEMDATA, i, 0);
		_freeSuggestions(&ps);
	}
	RemovePropW(hwnd, EDIT_PROP);
}