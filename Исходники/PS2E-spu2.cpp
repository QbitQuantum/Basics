EXPORT_C_(s32) SPU2test()
{
	if( !CheckSSE() ) return -1;

#ifdef _WIN32
	if (IsWindows8OrGreater())
	{
		for (int n = 0; mods[n] != nullptr; ++n)
		{
			if (mods[n] == XAudio2_27_Out)
			{
				mods[n] = XAudio2Out;
				break;
			}
		}
	}
#endif

	ReadSettings();
	if( SndBuffer::Test() != 0 )
	{
		// TODO : Implement a proper dialog that allows the user to test different audio out drivers.
		const wchar_t* wtf = mods[OutputModule]->GetIdent();
		SysMessage( L"The '%s' driver test failed.  Please configure\na different SoundOut module and try again.", wtf );
		return -1;
	}

	return 0;
}