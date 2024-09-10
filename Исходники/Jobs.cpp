bool JobSheduler::Queue(Job job)
{
	// Can't queue jobs twice
	if(job->IsQueued())
	{
		Logf("Tried to register a job twice", Logger::Warning);
		return false;
	}
	// Can't queue finished jobs
	if(job->IsFinished())
	{
		Logf("Tried to register a finished job", Logger::Warning);
		return false;
	}

	return m_impl->QueueUnchecked(job);
}