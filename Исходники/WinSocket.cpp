	Databuf.buf = (char *)buffer;
	receive = blocksize;
	int size = sizeof(in);
	if ((len = WSARecvFrom(this->sock, &Databuf, 1, &receive, 0, (SOCKADDR *)& in, &size, 0, 0)) ==  SOCKET_ERROR)
		return (-1);
	char cip[32];
	if ((ip = InetNtop( AF_INET, &in, cip, 32)) == "")
		{
			wprintf(L"InetNtop failed with error %u\n", WSAGetLastError());
			return -1;
		}
	return len;
}

int WinSocket::sendBinaryTo(void* data, std::string const &host, int port, int size)