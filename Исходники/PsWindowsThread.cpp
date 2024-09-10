void Thread::quit()
{
	mImpl->state = ThreadImpl::Stopped;
	ExitThread(0);
}