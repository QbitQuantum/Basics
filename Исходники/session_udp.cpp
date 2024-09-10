void SessionUDP::DoAsyncRecv()
{

#ifdef VHWD_WINDOWS


	TempPtrT<MyOverLappedEx> q=lkfq_recv.getq();
	if(!q)
	{
		return;
	}

	MyOverLappedEx &idat(*q);

	int bRet=WSARecvFrom(sk_local.sock,
						 &idat.dbuf[0],
						 idat.dbuf[1].buf?2:1,
						 &idat.size,
						 &iocp_flag_recv,
						 idat.peer,
						 idat.peer,
						 &idat.olap,
						 NULL);

	if(bRet!=0 && WSAGetLastError()!=WSA_IO_PENDING)
	{
		--m_nPendingRecv;
		Disconnect();
		return;
	}
	else
	{
		q.release();
	}

#else
	ep_ctl(EPOLLIN);
#endif
}