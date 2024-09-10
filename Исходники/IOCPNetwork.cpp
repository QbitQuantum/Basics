void InitializeServer(void)
{
	WSADATA wsadata;
	_wsetlocale(LC_ALL, L"korean");

	// Initialize Winsock
	// WSAStartup() :  프로그램에서 사용할 췬속 버전을 요청함으로써 윈속 라이브러리(WS2_32.DLL)를 초기화 하는 역할
	// msdn - The WSAStartup function initiates use of Winsock DLL bt a process

	// MAKEWORD(2,2)	: 프로그램이 요구하는 최상위 윈속 버전, 하위 8비트에 주 버전, 상위 8비트에 부 버전을 넣어서 전달
	//					: 만일 윈속 3.2 버전을 사용을 요청한다면 0x0203 또는 MAKEWORD(3,2)를 사용
	// wsadata			: 윈도우 운영체제가 제공하는 윈속 구현에 관한 정보(프로그램이 실제로 사용하게 될 윈속 버전,
	//					: 시스템이 지원하는 윈속 최상위 버전 등)를 얻을 수 있음. 하지만 실제로 이런 정보 사용 X
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		DisplayDebugText("InitializeServer :: WSAStartup Fail !!");
		exit(1);
	}

	// Create IOCP kernel object
	// if last argument is 0, Use kernel object by core count
	// CreateIoCompletionPort() : 입출력 완료 포트를 새로 생성.
	//							: 입출력 롼료 포트란 비동기 입출력 결과와 이 결과를 처리할 스레드에 관한 정보를 담고 있는 구조
	// msdn - Creates an input/output (I/O) completion port and associates it with a specified file handle, 
	//		or reates an I/O completion port that is not yet associated with a file handle, allowing association at a later time.
	ghIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if (NULL == ghIOCP)
	{
		DisplayDebugText("InitializeServer :: CreateIoCompletionPort Fail !!");
		exit(1);
	}

	return;
}