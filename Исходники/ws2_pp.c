BOOL CALLBACK DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    char szSysPath[MAX_PATH], szLibPath[MAX_PATH];
    WSADATA Wsa;

    switch(dwReason)
    {
        case DLL_PROCESS_ATTACH:
            l_hFakeDll = hInstance;

            if(MessageBoxA(NULL, "Connect to Packet Parser?", "Packet Parser", MB_YESNO|MB_ICONQUESTION)==IDNO)
            {
                use_dll = FALSE;
            }

            {// rewrite system DLL load path
                LPFNSETDLLDIRECTORYA lpfnSetDllDirectoryA = (LPFNSETDLLDIRECTORYA)GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "SetDllDirectoryA");

                if(lpfnSetDllDirectoryA)
                {
                    lpfnSetDllDirectoryA(".");
                }
            }

            GetSystemDirectoryA(szSysPath, _ARRAYSIZE(szSysPath));

            wsprintfA(szLibPath, "%s\\ws2_32.dll", szSysPath);

            l_hRealDll = LoadLibraryA(szLibPath);

            if(l_hRealDll)
            {
                if(l_hRealDll==l_hFakeDll)
                {// oops
                    FreeLibrary(l_hRealDll);
                    l_hRealDll = NULL;
                    MessageBoxA(NULL, "Attempted self-load.", "Library Error", MB_OK|MB_ICONSTOP);
                    return FALSE;
                }

#define LOADFUNC(x,y) l_WsFuncs.y = (x)GetProcAddress(l_hRealDll, #y)
                LOADFUNC(LPFN_CLOSESOCKET,closesocket);
                LOADFUNC(LPFN_CONNECT,connect);
                LOADFUNC(LPFN_HTONL,htonl);
                LOADFUNC(LPFN_HTONS,htons);
                LOADFUNC(LPFN_IOCTLSOCKET,ioctlsocket);
                LOADFUNC(LPFN_INET_ADDR,inet_addr);
                LOADFUNC(LPFN_INET_NTOA,inet_ntoa);
                LOADFUNC(LPFN_NTOHL,ntohl);
                LOADFUNC(LPFN_NTOHS,ntohs);
                LOADFUNC(LPFN_RECV,recv);
                LOADFUNC(LPFN_SELECT,select);
                LOADFUNC(LPFN_SEND,send);
                LOADFUNC(LPFN_SENDTO,sendto);
                LOADFUNC(LPFN_SETSOCKOPT,setsockopt);
                LOADFUNC(LPFN_SHUTDOWN,shutdown);
                LOADFUNC(LPFN_SOCKET,socket);
                LOADFUNC(LPFN_GETHOSTBYNAME,gethostbyname);
                LOADFUNC(LPFN_GETHOSTNAME,gethostname);
                LOADFUNC(LPFN_WSAGETLASTERROR,WSAGetLastError);
                LOADFUNC(LPFN_WSASTARTUP,WSAStartup);
                LOADFUNC(LPFN_WSACLEANUP,WSACleanup);
#undef LOADFUNC
				if(use_dll)
				{
					if(l_WsFuncs.WSAStartup(MAKEWORD(2,2), &Wsa))
					{
						FreeLibrary(l_hRealDll);
						l_hRealDll = NULL;
						MessageBoxA(NULL, "Failed to initialize actual Windows Sockets.", "Library Error", MB_OK|MB_ICONSTOP);
						return FALSE;
					}

					if((l_hSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==INVALID_SOCKET)
					{
						l_WsFuncs.WSACleanup();
						FreeLibrary(l_hRealDll);
						l_hRealDll = NULL;
						MessageBoxA(NULL, "Failed to create socket.", "Library Error", MB_OK|MB_ICONSTOP);
						return FALSE;
					}
					else
					{
						struct sockaddr_in sin;

						sin.sin_family = AF_INET;
						sin.sin_addr.s_addr = l_WsFuncs.htonl(SOCK_JOINIP(127,0,0,1));
						sin.sin_port = l_WsFuncs.htons(13554);

						if(connect(l_hSock, (struct sockaddr*)&sin, sizeof(sin))==SOCKET_ERROR)
						{
							l_WsFuncs.shutdown(l_hSock, SD_BOTH);
							l_WsFuncs.closesocket(l_hSock);
							l_hSock = INVALID_SOCKET;
							l_WsFuncs.WSACleanup();
							FreeLibrary(l_hRealDll);
							l_hRealDll = NULL;
							MessageBoxA(NULL, "Failed to connect to 127.0.0.1:13554 (TCP).", "Library Error", MB_OK|MB_ICONSTOP);
							use_dll = FALSE;
							//return FALSE;
						}
					}
				}
            }
            else
            {
                return FALSE;
            }
            break;
        case DLL_PROCESS_DETACH:
            if(l_hRealDll)
            {
                if(l_hSock!=INVALID_SOCKET)
                {
                    l_WsFuncs.shutdown(l_hSock, SD_BOTH);
                    l_WsFuncs.closesocket(l_hSock);
                    l_hSock = INVALID_SOCKET;
                }
                l_WsFuncs.WSACleanup();
                FreeLibrary(l_hRealDll);
                l_hRealDll = NULL;
            }
            l_hFakeDll = NULL;
            break;
    }
    return TRUE;

    // unused
    lpReserved;
}