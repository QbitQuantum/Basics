// main function for the engine thread
unsigned __stdcall recogThreadMain( void *param )
{
	int ret;
	Recog *recog = (Recog *)param;
	ret = j_recognize_stream(recog);
	_endthreadex(ret);
	return(ret);
}