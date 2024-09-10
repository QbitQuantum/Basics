/* Not thread safe 

   Assumes the string to convert was received from the console.
*/
static wchar_t* wide(const char* fname) {
    static wchar_t *buf=0;
    static int len=0;
    int n;
    ERR(n=MultiByteToWideChar(GetConsoleCP(),0,fname,(int)strlen(fname),buf,0));
    if(len<n) {
        if(buf)
            VirtualFree(buf,0,MEM_RELEASE);
        ERR(buf=VirtualAlloc(0,(n+1)*sizeof(wchar_t),MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE));
        len=n;
    }
    ERR(MultiByteToWideChar(GetConsoleCP(),0,fname,(int)strlen(fname),buf,len));
    return buf;
Error:
    exit(-1);
    return 0;
}