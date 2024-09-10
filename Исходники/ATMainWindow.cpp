void ATMainWindow_c::DoRegisterHotKey()
{
#ifdef _WIN32
	UnregisterHotKey( winId(), EZ_HOTKEY );

	if ( m_bHotkeyEnabled )
	{
		int iModifier = 0;
		int iKey = 0;

		if ( m_strHotkeyMod1 == "Ctrl" )	iModifier |= MOD_CONTROL;
		if ( m_strHotkeyMod1 == "Alt" )		iModifier |= MOD_ALT;
		if ( m_strHotkeyMod2 == "Shift" )	iModifier |= MOD_SHIFT;

		if ( !m_strHotkeyKey.isEmpty() )
		{
			iKey = m_strHotkeyKey.toUpper().at( 0 ).toLatin1();
			if ( iKey < 'A' || iKey > 'Z' ) iKey = 0;
		}

		if ( iModifier && iKey )
			RegisterHotKey( winId(), EZ_HOTKEY, iModifier, iKey );
	}
#endif
}