/*----------------------------------------------------------------------------*/ 
void	TImm::Init()
{
    CHAR szPath[MAX_PATH+1];
    
	if( GetSystemDirectoryA( szPath, MAX_PATH+1 ) ) 
	{
		strcat_s( szPath, "\\imm32.dll" );
		m_hDllImm32 = LoadLibraryA( szPath );
		if( m_hDllImm32 )
		{
			_ImmLockIMC		= (INPUTCONTEXT*(WINAPI *)( HIMC ))
				GetProcAddress( m_hDllImm32, "ImmLockIMC" );
			_ImmUnlockIMC	= (BOOL(WINAPI *)( HIMC ))
				GetProcAddress( m_hDllImm32, "ImmUnlockIMC" );
			_ImmLockIMCC	= (LPVOID(WINAPI *)( HIMCC ))
				GetProcAddress( m_hDllImm32, "ImmLockIMCC" );
			_ImmUnlockIMCC	= (BOOL(WINAPI *)( HIMCC ))
				GetProcAddress( m_hDllImm32, "ImmUnlockIMCC" );
		}
	}
}