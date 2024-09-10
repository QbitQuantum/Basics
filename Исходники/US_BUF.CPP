/** Sets the start and end points of the read and/or the write area within the intermediate 
buffer.

A start point is always within an area; an end point is always the first byte 
beyond the end of an area.

@param anArea The areas within the intermediate buffer for which the start 
and end points are to be set. These can be the read area and/or the write 
area, as indicated by the ERead and EWrite bits. Only these bits can be set, 
otherwise the function raises a STORE-Stream 17 panic.
@param aPtr The start point.
@param anEnd The end point.
@see MStreamBuf::TRead
@see MStreamBuf::TWrite */
EXPORT_C void TStreamBuf::SetBuf(TArea anArea,TUint8* aPtr,TUint8* anEnd)
	{
	__ASSERT_ALWAYS(!(anArea&~(ERead|EWrite)),Panic(EStreamAreaInvalid));
	if (anArea&ERead)
		SetBuf(ERead,aPtr,anEnd);
	if (anArea&EWrite)
		SetBuf(EWrite,aPtr,anEnd);
	}