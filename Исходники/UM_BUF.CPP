EXPORT_C TInt TBufBuf::UnderflowL(TInt)
//
// Establish the buffer's read area.
//
	{
	__ASSERT_ALWAYS(iMode&ERead,Panic(EMemCannotRead));
	__ASSERT_DEBUG(Ptr(ERead)==End(ERead),User::Invariant());
	TInt pos=Pos(ERead);
	TPtr8 seg=Buf().Ptr(pos);
	TUint8* ptr=(TUint8*)seg.Ptr();
	TInt len=seg.Length();
	if (iMode&ETruncate)
		{
		TInt left=Pos(EWrite)-pos;
		__ASSERT_DEBUG(left>=0,User::Invariant());
		if (left<len)
			len=left;
		}
	SetBuf(ERead,ptr,ptr+len);
	SetPos(ERead,pos+len);
	return len;
	}