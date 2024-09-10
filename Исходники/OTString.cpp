//inline bool vformat(const char * fmt, va_list vl, std::string & str_output)
//static
bool OTString::vformat(const char * fmt, va_list * pvl, std::string & str_Output)
{
    OT_ASSERT(NULL != fmt);
    OT_ASSERT(NULL != pvl);
    // ------------------
	int32_t size=0;
	int32_t nsize=0;
	char * buffer = NULL;
	va_list args;

#ifdef _WIN32
	va_list args_2 = *pvl;  //windows only.

	args = *pvl;
	size = _vscprintf(fmt,args) + 1;
#else
	va_copy(args, *pvl);
	size = 512;
#endif

    // ------------------------------------    
	buffer = new char[size+100];
	OT_ASSERT(NULL != buffer);
	OTPassword::zeroMemory(buffer, size+100);
    // ------------------------------------    

#ifdef _WIN32
	nsize = vsnprintf_s(buffer,size,size,fmt,args_2);
#else
	nsize = vsnprintf(buffer,size,fmt,args);
	va_end(args);
#endif

	OT_ASSERT(nsize >= 0);

    // fail -- delete buffer and try again
    // If nsize was 1024 bytes, then that would mean that it printed 1024 characters,
    // even though the actual string must be 1025 in length (to have room for the null
    // terminator.)
    // If size, the ACTUAL buffer, was 1024 (that is, if size <= nsize) then size would
    // LACK the necessary space to store the 1025th byte containing the null terminator.
    // Therefore we are forced to delete the buffer and make one that is nsize+1, so that
    // it will be 1025 bytes and thus have the necessary space for the terminator
    //
    if (size <= nsize) 
    {
	size  = nsize+1;
	delete buffer; buffer = NULL;
	buffer = new char[size+100];
	OT_ASSERT(NULL != buffer);
	OTPassword::zeroMemory(buffer, size+100);
	// ------------------------------------
#ifdef _WIN32
	nsize = vsnprintf_s(buffer,size,size,fmt,*pvl);
	va_end(args);
	va_end(args_2);
#else
	nsize = vsnprintf(buffer,size,fmt,*pvl);
#endif
	// ------------------------------------
	OT_ASSERT( nsize >= 0    );
    }
    OT_ASSERT(  size >  nsize);
    // ------------------------------------
    str_Output = buffer;
    delete buffer; buffer = NULL;
    return true;
}