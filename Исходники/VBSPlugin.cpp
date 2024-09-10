/**
*     Debug handler
*   http://bytes.com/forum/thread212702.html
*/            
void debug(char *fmt, ...)
{   
	if(WINDOWS_DEBUG) {
        char buffer[255];
        va_list argp;                    
        va_start(argp, fmt);
        vsprintf_s(buffer, fmt, argp);
        va_end(argp);
        OutputDebugString(buffer);
    } 
}