 osplatform_getter() : m_osplatform( 0 )
 {
     OSVERSIONINFOA osvi;
     osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
     if( GetVersionExA( & osvi ) )
         m_osplatform = osvi.dwPlatformId;
 }