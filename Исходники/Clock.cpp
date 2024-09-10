void CClock::Start(void)
{
	// 시계스레드 시작
	_beginthread(OnTimer, 0, this);
}