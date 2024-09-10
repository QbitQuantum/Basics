// Called before main
int intGlobalInit(){
	fprintf(stdout,"[i] I'm a global\n");

	//
	// These two result in populating the same LIFO queue
	// these are called by http://msdn.microsoft.com/en-GB/library/zb3b443a(v=vs.80).aspx
	// for source see CRT\SRC\ATONEXIT.C
	//
	atexit(atExit);
	_onexit(onExit);
	return 0;
}