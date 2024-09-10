/******************************************************************
 *		start_debugger
 *
 * Does the effective debugger startup according to 'format'
 */
static BOOL	start_debugger(PEXCEPTION_POINTERS epointers, HANDLE hEvent)
{
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING nameW;
    char *cmdline, *env, *p;
    HANDLE		hDbgConf;
    DWORD		bAuto = TRUE;
    PROCESS_INFORMATION	info;
    STARTUPINFOA	startup;
    char*		format = NULL;
    BOOL		ret = FALSE;
    char buffer[256];

    static const WCHAR AeDebugW[] = {'M','a','c','h','i','n','e','\\',
                                     'S','o','f','t','w','a','r','e','\\',
                                     'M','i','c','r','o','s','o','f','t','\\',
                                     'W','i','n','d','o','w','s',' ','N','T','\\',
                                     'C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\',
                                     'A','e','D','e','b','u','g',0};
    static const WCHAR DebuggerW[] = {'D','e','b','u','g','g','e','r',0};
    static const WCHAR AutoW[] = {'A','u','t','o',0};

    format_exception_msg( epointers, buffer, sizeof(buffer) );
    MESSAGE("wine: %s (thread %04x), starting debugger...\n", buffer, GetCurrentThreadId());

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.ObjectName = &nameW;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    RtlInitUnicodeString( &nameW, AeDebugW );

    if (!NtOpenKey( &hDbgConf, KEY_ALL_ACCESS, &attr ))
    {
        char buffer[64];
        KEY_VALUE_PARTIAL_INFORMATION *info;
        DWORD format_size = 0;

        RtlInitUnicodeString( &nameW, DebuggerW );
        if (NtQueryValueKey( hDbgConf, &nameW, KeyValuePartialInformation,
                             NULL, 0, &format_size ) == STATUS_BUFFER_OVERFLOW)
        {
            char *data = HeapAlloc(GetProcessHeap(), 0, format_size);
            NtQueryValueKey( hDbgConf, &nameW, KeyValuePartialInformation,
                             data, format_size, &format_size );
            info = (KEY_VALUE_PARTIAL_INFORMATION *)data;
            RtlUnicodeToMultiByteSize( &format_size, (WCHAR *)info->Data, info->DataLength );
            format = HeapAlloc( GetProcessHeap(), 0, format_size+1 );
            RtlUnicodeToMultiByteN( format, format_size, NULL,
                                    (WCHAR *)info->Data, info->DataLength );
            format[format_size] = 0;

            if (info->Type == REG_EXPAND_SZ)
            {
                char* tmp;

                /* Expand environment variable references */
                format_size=ExpandEnvironmentStringsA(format,NULL,0);
                tmp=HeapAlloc(GetProcessHeap(), 0, format_size);
                ExpandEnvironmentStringsA(format,tmp,format_size);
                HeapFree(GetProcessHeap(), 0, format);
                format=tmp;
            }
            HeapFree( GetProcessHeap(), 0, data );
        }

        RtlInitUnicodeString( &nameW, AutoW );
        if (!NtQueryValueKey( hDbgConf, &nameW, KeyValuePartialInformation,
                              buffer, sizeof(buffer)-sizeof(WCHAR), &format_size ))
       {
           info = (KEY_VALUE_PARTIAL_INFORMATION *)buffer;
           if (info->Type == REG_DWORD) memcpy( &bAuto, info->Data, sizeof(DWORD) );
           else if (info->Type == REG_SZ)
           {
               WCHAR *str = (WCHAR *)info->Data;
               str[info->DataLength/sizeof(WCHAR)] = 0;
               bAuto = atoiW( str );
           }
       }

       NtClose(hDbgConf);
    }

    if (format)
    {
        cmdline = HeapAlloc(GetProcessHeap(), 0, strlen(format) + 2*20);
        sprintf(cmdline, format, GetCurrentProcessId(), hEvent);
        HeapFree(GetProcessHeap(), 0, format);
    }
    else
    {
        cmdline = HeapAlloc(GetProcessHeap(), 0, 80);
        sprintf(cmdline, "winedbg --auto %d %ld",
                GetCurrentProcessId(), (ULONG_PTR)hEvent);
    }

    if (!bAuto)
    {
	HMODULE			mod = GetModuleHandleA( "user32.dll" );
	MessageBoxA_funcptr	pMessageBoxA = NULL;

	if (mod) pMessageBoxA = (MessageBoxA_funcptr)GetProcAddress( mod, "MessageBoxA" );
	if (pMessageBoxA)
	{
            static const char msg[] = ".\nDo you wish to debug it?";
	    char buffer[256];

            format_exception_msg( epointers, buffer, sizeof(buffer)-sizeof(msg) );
            strcat( buffer, msg );
	    if (pMessageBoxA( 0, buffer, "Exception raised", MB_YESNO | MB_ICONHAND ) == IDNO)
	    {
		TRACE("Killing process\n");
		goto EXIT;
	    }
	}
    }

    /* make WINEDEBUG empty in the environment */
    env = GetEnvironmentStringsA();
    for (p = env; *p; p += strlen(p) + 1)
    {
        if (!memcmp( p, "WINEDEBUG=", sizeof("WINEDEBUG=")-1 ))
        {
            char *next = p + strlen(p);
            char *end = next + 1;
            while (*end) end += strlen(end) + 1;
            memmove( p + sizeof("WINEDEBUG=") - 1, next, end + 1 - next );
            break;
        }
    }

    TRACE("Starting debugger %s\n", debugstr_a(cmdline));
    memset(&startup, 0, sizeof(startup));
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESHOWWINDOW;
    startup.wShowWindow = SW_SHOWNORMAL;
    ret = CreateProcessA(NULL, cmdline, NULL, NULL, TRUE, 0, env, NULL, &startup, &info);
    FreeEnvironmentStringsA( env );

    if (ret)
    {
        /* wait for debugger to come up... */
        HANDLE handles[2];
        CloseHandle(info.hThread);
        handles[0]=hEvent;
        handles[1]=info.hProcess;
        WaitForMultipleObjects(2, handles, FALSE, INFINITE);
        CloseHandle(info.hProcess);
    }
    else ERR("Couldn't start debugger (%s) (%d)\n"
             "Read the Wine Developers Guide on how to set up winedbg or another debugger\n",
             debugstr_a(cmdline), GetLastError());
EXIT:
    HeapFree(GetProcessHeap(), 0, cmdline);
    return ret;
}