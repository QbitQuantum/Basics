// 线程运行接口对象
void CQueueThread::run( void *param )
{
	while( _inited ) {
		Process() ;
	}
}