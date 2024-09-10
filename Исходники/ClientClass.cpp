// sendPacket ( sizeof( data ), type 값 , data 의 주소값 );
void AsynchronousClientClass::sendPacket(const BYTE data_size, const BYTE type, BYTE* data_start_pointer) {
	// 실제 최대 버퍼 사이즈 보다 데이터 길이가 커지면 안된다.
	if (MAX_BUF_SIZE < (data_size + 2)) {
#ifdef _DEBUG
		// 아래와 같은 에러가 발생하게 된다면, 버퍼 사이즈를 건드리기 보다 실제 데이터 크기를 압축해 줄여 보낼 수 있도록 하자
		printf("[ code LINE %d ] [ code FUNCTION %s ] SendPacket class ERROR :: data size overed MAX_BUF_SIZE\n", __LINE__, __FUNCTION__);
#endif
	}
	else {
		// 패킷 안의 실제 내용 생성
		m_sendbuf[0] = data_size + 2;
		m_sendbuf[1] = type;

		if (nullptr != data_start_pointer) { memcpy(&m_sendbuf[2], data_start_pointer, m_sendbuf[0]); }

		m_wsa_sendbuf.len = m_sendbuf[0];
		DWORD ioByteSize;
		m_retval = WSASend(m_sock, &m_wsa_sendbuf, 1, &ioByteSize, 0, NULL, NULL);
		if (SOCKET_ERROR == m_retval) {
			// 비동기 소켓이라 그냥 리턴, 검사 해주어야 함
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				int err_no = WSAGetLastError();
				error_quit(L"sendPacket()", err_no);
			}
		}
	}
}