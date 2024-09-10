	bool SetError(int nResult, bool bFree = true) {
		if (!myErrRes 
			&& !SQL_SUCCEEDED(nResult)) {
				myErrBuf.Grow(1024);
				myErrState.Grow(6);
				SQLSMALLINT tlen = 0;
				if (!SQLGetDiagRec(myType, myHandle, 1, (SQLCHAR*) myErrState.GetBuffer(), &myErrCode, (SQLCHAR*) (myErrBuf.GetBuffer())+8, myErrBuf.Length()-8, &tlen)) {
					myErrBuf[0] = '(';
					memcpy(myErrBuf+1, (const char *)myErrState, 5);
					myErrBuf[6] = ')';
					myErrBuf[7] = ' ';
					myErrBuf.Grow(min(tlen+8,myErrBuf.Length()-8));
					myErrRes = nResult;
				} else {
					myErrState = "00000";
					myErrBuf = "(00000) No error.";
					myErrRes = nResult;
				}
				if (bFree) {
					SQLFreeHandle(myType, myHandle);
					myHandle = 0;
				}
				return false;
		}
		return true;
	}