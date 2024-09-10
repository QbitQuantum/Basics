__int64 gpt() {
	FILETIME a,b,c,d;
	GetProcessTimes(GetCurrentProcess(), &a,&b,&c,&d);
	return *(__int64*)&d;
}