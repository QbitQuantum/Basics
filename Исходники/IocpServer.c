int main(int argc, char* argv[]) {
	
	// wsaData
	WSADATA wsaData;
	// Completion Port
	HANDLE hComPort;
	// 시스템 관련 정보를 저장합니다.
	SYSTEM_INFO sysInfo;
	// 버퍼 관련된 정보를 저장합니다.
	LPPER_IO_DATA ioInfo;
	// 클라이언트 소켓과 정보를 저장하는 구조체 입니다.
	LPPER_HANDLE_DATA handleInfo;

	// 서버 소켓입니다.
	SOCKET hServSock;
	// 서버 주소에 관련된 정보를 저장합니다.
	SOCKADDR_IN servAdr;
	int recvBytes, i, flags = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup error");
	}

	// CompletionPort 생성
	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	
	// 시스템 정보를 불러옵니다. 동시에 프로세서 수만큼 스레드를 생성합니다.
	GetSystemInfo(&sysInfo);
	for (i = 0; i < sysInfo.dwNumberOfProcessors; i++)
		_beginthreadex(NULL, 0, EchoThreadMain, (LPVOID)hComPort, 0, NULL);

	// 서버 소켓 생성
	hServSock = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(argv[1]);

	// bind
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind error!");

	// listen
	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("Listen error");

	while (1) {
		
		// 클라이언트 소켓
		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);

		// Client Accept하고 handleInfo 구조체에 연결
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &addrLen);
		handleInfo = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		handleInfo->hClntSock = hClntSock;
		handleInfo->clntAdr = clntAdr;
		memcpy(&(handleInfo->clntAdr), &clntAdr, addrLen);

		// CompletionPort에 client socket 연결해서 완료정보를 넘기도록 함
		CreateIoCompletionPort((HANDLE)hClntSock, hComPort, (DWORD)handleInfo, 0);

		// io관련된 구조체 생성 후 recv 대기
		ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
		ioInfo->wsaBuf.len = BUF_SIZE;
		ioInfo->wsaBuf.buf = ioInfo->buffer;
		ioInfo->rwMode = READ;
		WSARecv(handleInfo->hClntSock, &(ioInfo->wsaBuf.buf), 1, &recvBytes, &flags, &(ioInfo->overlapped), NULL);
	}

	getchar();
	return 0;
}