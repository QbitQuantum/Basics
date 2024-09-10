//---------------------------------------------------------------------------
tjs_uint TJS_INTF_METHOD tTVPMemoryStream::Write(const void *buffer, tjs_uint write_size)
{
	// writing may increase the internal buffer size.
	if(Reference) TVPThrowExceptionMessage(TVPWriteError);

	tjs_uint newpos = CurrentPos + write_size;
	if(newpos >= AllocSize)
	{
		// exceeds AllocSize
		tjs_uint onesize;
		if(AllocSize < 64*1024) onesize = 4*1024;
		else if(AllocSize < 512*1024) onesize = 16*1024;
		else if(AllocSize < 4096*1024) onesize = 256*1024;
		else onesize = 2024*1024;
		AllocSize += onesize;

		if(CurrentPos + write_size >= AllocSize) // still insufficient ?
		{
			AllocSize = CurrentPos + write_size;
		}

		Block = Realloc(Block, AllocSize);

		if(AllocSize && !Block)
			TVPThrowExceptionMessage(TVPInsufficientMemory);
			// this exception cannot be repaird; a fatal error.
	}

	memcpy((tjs_uint8*)Block + CurrentPos, buffer, write_size);

	CurrentPos = newpos;

	if(CurrentPos > Size) Size = CurrentPos;

	return write_size;
}