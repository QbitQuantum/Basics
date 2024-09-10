// 최초 한번만 실행
void zmodifyer::init() {

	static bool first = true;

	if( !first )
		return;

	first = false;

	//g_StdOut.SetStream( NULL );

#if defined(_WIN32) && !defined(UNDER_CE)
	SetFileApisToOEM(); // ??
#endif
}