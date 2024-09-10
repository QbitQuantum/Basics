static void DbgPrint_s(const char* format, ...)
{       
	static char dbg_msg_buff[0x1000]; 
        if (format)
        {
                va_list args;
                va_start(args, format);
                int len = wvsprintfA(dbg_msg_buff, format, args);
                va_end(args);
		OutputDebugStringA(dbg_msg_buff);
        }
}