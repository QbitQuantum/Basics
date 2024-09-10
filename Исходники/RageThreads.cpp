const char *RageThread::GetCurThreadName()
{
	return GetThreadNameByID( GetCurrentThreadID() );
}