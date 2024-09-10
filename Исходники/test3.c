/**
 * main
 * 
 * executable entry point
 */
int __cdecl main( int argc, char **argv ) 
{
    /* local variables */
    DWORD dwSocketError;

    SOCKET sock = INVALID_SOCKET;


    /* PAL initialization */
    if ( (PAL_Initialize(argc, argv)) != 0 )
    {
        return( FAIL );
    }


    /* try a socket call */
    sock = WSASocketA(  AF_INET,
                        SOCK_STREAM,
                        IPPROTO_IP,
                        NULL,
                        0,
                        WSA_FLAG_OVERLAPPED
                    );


    if ( sock != INVALID_SOCKET )
    {
        /* check the socket-specific error code */    
        closesocket( sock );
        Fail(   "WSASocketA call succeeded before call to WSAStartup\n" ); 
    }

    dwSocketError = GetLastError();
    if ( dwSocketError != WSANOTINITIALISED )
    {
        Fail(   "WSASocketA call failed with error code %d "
                "instead of WSANOTINITIALISED\n",
                dwSocketError ); 
    }
    
    /* PAL termination */
    PAL_Terminate();
    return PASS; 
}