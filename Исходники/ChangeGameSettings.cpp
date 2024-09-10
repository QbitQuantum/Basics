void ChangeGameSettings::OnOK() 
{
	// TODO: Add extra validation here
	IniFile ini;
	ini.ReadFile( SpecialFiles::PREFERENCES_INI_PATH );

	if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_OPENGL) )
		ini.SetValue( "Options", "VideoRenderers", (RString)"opengl" );
	else if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_DIRECT3D) )
		ini.SetValue( "Options", "VideoRenderers", (RString)"d3d" );
	else
		ini.SetValue( "Options", "VideoRenderers", RString() );


	if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SOUND_DIRECTSOUND_HARDWARE) )
		ini.SetValue( "Options", "SoundDrivers", (RString)"DirectSound" );
	else if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SOUND_DIRECTSOUND_SOFTWARE) )
		ini.SetValue( "Options", "SoundDrivers", (RString)"DirectSound-sw" );
	else if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SOUND_WAVEOUT) )
		ini.SetValue( "Options", "SoundDrivers", (RString)"WaveOut" );
	else if( BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_SOUND_NULL) )
		ini.SetValue( "Options", "SoundDrivers", (RString)"null" );
	else
		ini.SetValue( "Options", "SoundDrivers", RString() );


	if( BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_FORCE_60HZ) )
	{
		ini.SetValue( "Options", "RefreshRate", 60 );
	}
	else
	{
		int iRefresh = 0;
		ini.GetValue( "Options", "RefreshRate", iRefresh );
		if( iRefresh == 60 )
			ini.SetValue( "Options", "RefreshRate", 0 );
	}
	ini.SetValue( "Options", "LogToDisk",		BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_LOG_TO_DISK) );
	ini.SetValue( "Options", "ShowLogOutput",	BST_CHECKED == IsDlgButtonChecked(IDC_CHECK_SHOW_LOG_WINDOW) );


	if( !ini.WriteFile(SpecialFiles::PREFERENCES_INI_PATH) )
	{
		RString sError = ssprintf( ERROR_WRITING_FILE.GetValue(), SpecialFiles::PREFERENCES_INI_PATH.c_str(), ini.GetError().c_str() );
		Dialog::OK( sError );
	}

	CDialog::OnOK();
}