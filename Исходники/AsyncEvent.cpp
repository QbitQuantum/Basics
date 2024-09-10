bool AsyncEvents::wait(bool all, int ms)
{
	int result = WaitForMultipleObjectsEx(m_count, &handle(0), all, ms, true);
	if (result == WAIT_IO_COMPLETION)
		return false;

	m_activated = result - WAIT_OBJECT_0;

	return true;
}