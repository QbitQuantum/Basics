BOOL CSocketObj::ConnectSer(CCustomIOCPBaseList &IOCPList, LPCTSTR SerAddr, int Port, int IncRefNumber)
{
	BOOL resu = FALSE;
	ADDRINFOT _Hints;
	int _Retval;
	PADDRINFOT _ResultAddInfo;
	PADDRINFOT _NextAddInfo;
	DWORD _AddrStringLen;
	LPTSTR _AddrString;

	assert(mIsSerSocket == FALSE);
	ZeroMemory(&_Hints, sizeof(_Hints));
	_Hints.ai_family = AF_UNSPEC;
	_Hints.ai_socktype = SOCK_STREAM;
	_Hints.ai_protocol = IPPROTO_TCP;
	_Retval = GetAddrInfo(SerAddr, to_tstring(Port).c_str(), &_Hints, &_ResultAddInfo);
	if (_Retval != 0) {
		return FALSE;
	}
	_NextAddInfo = _ResultAddInfo;

	// 申请缓冲区
	_AddrString = new TCHAR[ADDR_STRING_MAX_LEN];

	while (_NextAddInfo != NULL) {
		_AddrStringLen = ADDR_STRING_MAX_LEN;
		// 获取
#ifdef _DEBUG
		if (WSAAddressToString(_NextAddInfo->ai_addr, (DWORD)_NextAddInfo->ai_addrlen, NULL,
			_AddrString, &_AddrStringLen) == 0) {
			// 改为真实长度,这里的_AddrStringLen包含了末尾的字符#0，所以要减去这个#0的长度
			_AddrStringLen--;
			OutputDebugStr(_T("ai_addr:%s,ai_flags:%d,ai_canonname=%s\n"),
				_AddrString, _NextAddInfo->ai_flags, _NextAddInfo->ai_canonname);
		} else {
			OutputDebugStr(_T("WSAAddressToString Error:%d\n"), WSAGetLastError());
		}
#endif
		mSock = WSASocket(_NextAddInfo->ai_family, _NextAddInfo->ai_socktype,
			_NextAddInfo->ai_protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (mSock != INVALID_SOCKET) {
			if (connect(mSock, _NextAddInfo->ai_addr, (INT)_NextAddInfo->ai_addrlen) == SOCKET_ERROR) {
				DWORD LastError = WSAGetLastError();

				OutputDebugStr(_T("连接%s失败：%d\n"), _AddrString, LastError);

				closesocket(mSock);
				WSASetLastError(LastError);
				mSock = INVALID_SOCKET;
			} else {
				mOwner = &IOCPList;
				// 增加引用
				IncRefCount(IncRefNumber);
				resu = IOCPList.AddSockBase(this);
				if (!resu) {
					DWORD LastError = WSAGetLastError();
					OutputDebugStr(_T("添加%s到列表中失败：%d\n"), _AddrString, LastError);
					closesocket(mSock);
					WSASetLastError(LastError);
					mSock = INVALID_SOCKET;
					// 减少引用
					DecRefCount(IncRefNumber);
				}
				break;
			}
		}
		_NextAddInfo = _NextAddInfo->ai_next;
	}
	delete[] _AddrString;
	FreeAddrInfo(_ResultAddInfo);
	return resu;
}