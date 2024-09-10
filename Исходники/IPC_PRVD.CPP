void CIpcStreamProvd::GetData(TDes8 &aDesc,TUint /*options*/,TSockAddr* /*anAddr*/)
	{
	__ASSERT_DEBUG(iConnection,Panic(EBadWriteCall));
	__ASSERT_DEBUG(iSocket,Panic(EBadWriteCall));

	CCirBuffer& buf=((CIpcStreamProvd *)iConnection)->iBuffer;

	__ASSERT_DEBUG(aDesc.Length()<=buf.Count(),Panic(EReadGetTooMuch));

	buf.Remove((TUint8 *)aDesc.Ptr(),aDesc.Length());
	iConnection->CanSend();
	}