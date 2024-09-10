/**
 @brief 
 @param numWorkThread 0이면 시스템 코어에 맞춰 자동
*/
void XEWinSocketSvr::Create( WORD port, int numWorkThread )
{
	XBREAK( port == 0 );
	if( XWinNetwork::sStartUp() == false ) {
		XALERT( "WSAStartup failed" );
		return;
	}
	//
//	m_Socket = socket( AF_INET, SOCK_STREAM, 0 );
	m_Socket = WSASocket( PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	if( m_Socket == INVALID_SOCKET ) {
		XALERT( "create socket failed" );
		return;
	}
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	addr.sin_addr.S_un.S_addr = htonl( INADDR_ANY );
	if( bind( m_Socket, ( struct sockaddr * )&addr, sizeof( addr ) ) == SOCKET_ERROR ) {
		XBREAK(1);
		XALERT( "Network bind error" );
		Destroy();
		return;
	}
	//
	m_Port = port;
	// 클라로부터 접속을 받을 준비
	if( listen( m_Socket, SOMAXCONN ) == SOCKET_ERROR ) {
		XALERT( "Network::listen error" );
		Destroy();
		return;
	}
	//
	m_pUserMng = CreateUserMng( m_maxConnect );
	XBREAK( m_pUserMng == NULL );
	// 유저 커스텀 create
	OnCreate(); // virtual
	// IOCP 객체 생성
	m_hIOCP = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 ); 
	// 워커 스레드 생성
	SYSTEM_INFO si;
	memset( &si, 0, sizeof(si));
	GetSystemInfo( &si );
#if defined(_DEBUG) && !defined(_XBOT)
	const int numThread = 4;		// 개발중엔 편의상 스레드 적게쓴다.
#else
	const int numThread = (numWorkThread == 0)? 
														(int)(si.dwNumberOfProcessors * 2)
													: numWorkThread;
#endif
	XBREAK( numThread <= 0 || numThread > 32 );
	for( int i = 0; i < numThread; ++i ) {
		m_aryThreadWork.push_back( CreateWorkThread() );
	}
	// accept( 클라이언트로부터의 접속대기 ) 스레드 생성
	m_thAccept = CreateAcceptThread();
	//
#if _DEV_LEVEL <= DLV_OPEN_BETA
	m_timerSec.Set( 1.f );
#endif
}