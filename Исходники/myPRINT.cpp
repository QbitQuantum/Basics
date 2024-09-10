myPRINT::myPRINT(BOOL bUseConsole)
{
	m__bAllocConsole	= FALSE;
	m__bUseConsole		= bUseConsole;
	INT	iReturnVal = 0;

	m__lpFile = NULL;
	if (m__bUseConsole == FALSE)
		return;

	// STD_INPUT_HANDLE 과 STD_OUTPUT_HANDLE 은 Redirected 됐을 수도
	// 있으므로, 먼저 STD_ERROR_HANDLE 을 얻는다.
	// 만약 성공하면 이미 유용한 콘솔은 있고 그렇지 않다면
	// AllocConsole() 을 이용해서 필요한 콘솔을 생성한다.
	m__CONERR = GetStdHandle(STD_ERROR_HANDLE);
	if (m__CONERR == INVALID_HANDLE_VALUE) {
		(VOID) MessageBox(
			NULL,
			TEXT("GetStdHandle(STD_ERROR_HANDLE) failed!"),
			TEXT("Message Box: Error!"),
			MB_OK
		);
		iReturnVal = -1;
		goto NEXT;
	} else if (m__CONERR == NULL) {
		// 유용한 콘솔이 없다!
		// AllocConsole() 을 이용해서 새로 만들자.
		if (!AllocConsole()) {
			(VOID) MessageBox(
				NULL,
				TEXT("AllocHandle(VOID) failed!"),
				TEXT("Message Box: Error!"),
				MB_OK
			);
			iReturnVal = -1;
			goto NEXT;
		}
		m__bAllocConsole = TRUE;

		m__CONERR = GetStdHandle(STD_ERROR_HANDLE);
		if (m__CONERR == INVALID_HANDLE_VALUE || m__CONERR == NULL) {
			INT	i = *((PINT) 0);
		}
	}

	// 사용가능한 콘솔이 있다!
	m__CONOUT = GetStdHandle(STD_OUTPUT_HANDLE);
	if (m__CONOUT == INVALID_HANDLE_VALUE) {
		(VOID) MessageBox(
			NULL,
			TEXT("GetStdHandle(STD_OUTPUT_HANDLE) failed!"),
			TEXT("Message Box: Error!"),
			MB_OK
		);
		iReturnVal = -1;
		goto NEXT;
	} else if (m__CONOUT == NULL) {
		// 이럴수가...
		// 이미 사용가능한 콘솔이 있지 않나?...
		(VOID) MessageBox(
			NULL,
			TEXT("GetStdHandle(STD_OUTPUT_HANDLE): ")
			TEXT("No Associated Standard Output Handle!"),
			TEXT("Message Box: Warning!"),
			MB_OK
		);
		iReturnVal = -1;
		goto NEXT;
	}


NEXT:
	if (iReturnVal != 0) {
		if (m__bAllocConsole == TRUE) {
			if (0 && !FreeConsole()) {
				(VOID) MessageBox(
					NULL,
					TEXT("FreeConsole(VOID) failed!"),
					TEXT("Message Box: Error!"),
					MB_OK
				);
			}
			m__bAllocConsole = FALSE;
		}
		m__CONOUT = NULL;
		m__CONERR = NULL;
	}
}