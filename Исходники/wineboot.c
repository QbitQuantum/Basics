/* create the platform-specific environment registry keys */
static void create_environment_registry_keys( void )
{
    static const WCHAR EnvironW[]  = {'S','y','s','t','e','m','\\',
                                      'C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\',
                                      'C','o','n','t','r','o','l','\\',
                                      'S','e','s','s','i','o','n',' ','M','a','n','a','g','e','r','\\',
                                      'E','n','v','i','r','o','n','m','e','n','t',0};
    static const WCHAR NumProcW[]  = {'N','U','M','B','E','R','_','O','F','_','P','R','O','C','E','S','S','O','R','S',0};
    static const WCHAR ProcArchW[] = {'P','R','O','C','E','S','S','O','R','_','A','R','C','H','I','T','E','C','T','U','R','E',0};
    static const WCHAR x86W[]      = {'x','8','6',0};
    static const WCHAR IA64W[]     = {'I','A','6','4',0};
    static const WCHAR AMD64W[]    = {'A','M','D','6','4',0};
    static const WCHAR ProcIdW[]   = {'P','R','O','C','E','S','S','O','R','_','I','D','E','N','T','I','F','I','E','R',0};
    static const WCHAR ProcLvlW[]  = {'P','R','O','C','E','S','S','O','R','_','L','E','V','E','L',0};
    static const WCHAR ProcRevW[]  = {'P','R','O','C','E','S','S','O','R','_','R','E','V','I','S','I','O','N',0};
    static const WCHAR PercentDW[] = {'%','d',0};
    static const WCHAR Percent04XW[] = {'%','0','4','x',0};
    static const WCHAR IntelCpuDescrW[]  = {'%','s',' ','F','a','m','i','l','y',' ','%','d',' ','M','o','d','e','l',' ','%','d',
                                            ' ','S','t','e','p','p','i','n','g',' ','%','d',',',' ','G','e','n','u','i','n','e','I','n','t','e','l',0};

    HKEY env_key;
    SYSTEM_CPU_INFORMATION sci;
    WCHAR buffer[60];
    const WCHAR *arch;

    NtQuerySystemInformation( SystemCpuInformation, &sci, sizeof(sci), NULL );

    if (RegCreateKeyW( HKEY_LOCAL_MACHINE, EnvironW, &env_key )) return;

    sprintfW( buffer, PercentDW, NtCurrentTeb()->Peb->NumberOfProcessors );
    set_reg_value( env_key, NumProcW, buffer );

    switch(sci.Architecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64: arch = AMD64W; break;
    case PROCESSOR_ARCHITECTURE_IA64:  arch = IA64W; break;
    default:
    case PROCESSOR_ARCHITECTURE_INTEL: arch = x86W; break;
    }
    set_reg_value( env_key, ProcArchW, arch );

    /* TODO: currently hardcoded Intel, add different processors */
    sprintfW( buffer, IntelCpuDescrW, arch, sci.Level, HIBYTE(sci.Revision), LOBYTE(sci.Revision) );
    set_reg_value( env_key, ProcIdW, buffer );

    sprintfW( buffer, PercentDW, sci.Level );
    set_reg_value( env_key, ProcLvlW, buffer );

    /* Properly report model/stepping */
    sprintfW( buffer, Percent04XW, sci.Revision );
    set_reg_value( env_key, ProcRevW, buffer );

    RegCloseKey( env_key );
}