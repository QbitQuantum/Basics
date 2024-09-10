COwnThread::COwnThread(void)
{

	//proc.proccess = &COwnThread::process;
	handle = (HANDLE)_beginthreadex(NULL,0,stdcall,this,0,NULL);
}