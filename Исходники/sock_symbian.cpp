/*
 * Receive data.
 */
PJ_DEF(pj_status_t) pj_sock_recvfrom(pj_sock_t sock,
				     void *buf,
				     pj_ssize_t *len,
				     unsigned flags,
				     pj_sockaddr_t *from,
				     int *fromlen)
{
    PJ_CHECK_STACK();

    PJ_ASSERT_RETURN(sock && buf && len && from && fromlen, PJ_EINVAL);
    PJ_ASSERT_RETURN(*len > 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(*fromlen >= (int)sizeof(pj_sockaddr_in), PJ_EINVAL);

    // Return failure if access point is marked as down by app.
    PJ_SYMBIAN_CHECK_CONNECTION();

    CPjSocket *pjSock = (CPjSocket*)sock;
    RSocket &rSock = pjSock->Socket();

    if (pjSock->Reader()) {
	CPjSocketReader *reader = pjSock->Reader();

	while (reader->IsActive() && !reader->HasData()) {
	    User::WaitForAnyRequest();
	}

	if (reader->HasData()) {
	    TPtr8 data((TUint8*)buf, (TInt)*len);
	    TInetAddr inetAddr;

	    reader->ReadData(data, &inetAddr);

	    *len = data.Length();

	    if (from && fromlen) {
		return PjSymbianOS::Addr2pj(inetAddr, *(pj_sockaddr*)from, 
					    fromlen);
	    } else {
	    	return PJ_SUCCESS;
	    }
	}
    }

    TInetAddr inetAddr;
    TRequestStatus reqStatus;
    TSockXfrLength recvLen;
    TPtr8 data((TUint8*)buf, (TInt)*len, (TInt)*len);

    rSock.RecvFrom(data, inetAddr, flags, reqStatus, recvLen);
    User::WaitForRequest(reqStatus);

    if (reqStatus == KErrNone) {
	//*len = (TInt)recvLen.Length();
	*len = data.Length();
	return PjSymbianOS::Addr2pj(inetAddr, *(pj_sockaddr*)from, fromlen);
    } else {
	*len = -1;
	*fromlen = -1;
	return PJ_RETURN_OS_ERROR(reqStatus.Int());
    }
}