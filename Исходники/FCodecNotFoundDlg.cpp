void FCodecNotFoundDlg::OnCreated()
{
	SetMinSize(640, 480); 
	SetIcon(LoadIcon(_Module.get_m_hInst(), MAKEINTRESOURCE(IDI_MAIN)));

	FString Str;
	GetWindowText(Str);

	SetWindowText(LTV_APP_NAME": Codec not found"); 

	if (FAILED(m_pW.Navigate(g_AppSettings.AppDir(Str))))
	{
		MessageBox("Cannot load error file.", "Error loading dialog", MB_OK | MB_ICONERROR); 
		DestroyWindow();
	}

	SetFocus(); 
	SetActiveWindow(); 
}