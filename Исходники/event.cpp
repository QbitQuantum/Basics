void NaClEventLoop::wait(const EventTrigger &trigger, EventCallback *callback)
{
	Trace("NaClEventLoop.wait: callback=%p", callback);

	trigger.completion.reset(&m_instance, callback);
}