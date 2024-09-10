EXPORT_C void CRtpHandlerBase::SaveReadStatus(TDes8& aClientBuf)
	{	
	__RTP_LOG1(_L("CRtpHandlerBase [0x%x]::SaveClientStatus"), this);
	__RTP_LOG2(_L("\taClientBuffer at 0x%x, of Length %d"), aClientBuf.Ptr(), aClientBuf.Length());
	ASSERT(iDataObserver); //With out DataObserver the app shouldnot attempt a read
	iClientDataPtr = &aClientBuf;
	}