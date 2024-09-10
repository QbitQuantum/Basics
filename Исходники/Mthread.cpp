/**
 *	使用 create_thread 创建的线程，线程过程必须自己显示的调用exit_thread，否则可能造成句柄泄漏
 */
void MThread::exit_thread(void)
{
#ifndef LINUXCODE
	_endthreadex(0);
#else
	pthread_exit(0);
#endif
}