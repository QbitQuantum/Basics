SerialPortBase::~SerialPortBase(void)
{
	ClosePort();
	if(pthread != NULL)
	{
//      pthread->m_bTerminated = true;
		pthread->ThreadResume();//线程恢复.
		pthread->Terminate();
		pthread->WaitFor();
		delete pthread;
		pthread = NULL;
	}
}