void runonce() {
#ifdef _MSC_VER
	if( ! s_hasRunOnceRun ) {
		_setmaxstdio( 2048 );
		s_hasRunOnceRun = true;
	}
#endif
}