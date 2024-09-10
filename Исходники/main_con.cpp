void trace(const char* fmt, ...){
	char buf [256];
	va_list va;
	va_start(va,fmt);
	int n = wvsprintfA(buf,fmt,va);
	va_end(va);
	if(n>0)WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),buf,n,(DWORD*)&n,0);
}