void UT_UTF8String::appendBuf (const UT_ByteBuf & buf, UT_UCS4_mbtowc & converter)
{
	UT_uint32 i;
	UT_UCS4Char wc;
	const UT_Byte *ptr = buf.getPointer(0);
	
	for (i = 0; i < buf.getLength(); i++) 
	{
	  if (converter.mbtowc(wc, static_cast<char>(ptr[i])))
	        pimpl->appendUCS4(&wc, 1);
 	}
}