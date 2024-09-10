NTSTATUS COMPLETION_PORT_IMPL::Remove(ULONG& key, ULONG& value, NTSTATUS& status, ULONG& info, PLARGE_INTEGER timeout)
{

	// try remove the completion entry first
	COMPLETION_PACKET *packet = queue.Head();
	if (!packet)
	{
		// queue thread here
		COMPLETION_WAITER waiter(Current);
		waiter.Stop( waiter_list, timeout );
		packet = waiter.GetPacket();
	}
	// this thread must be active... don't block ourselves
	else if (RUNLIST_ENTRY::NumActiveThreads() > num_threads )
	{
		// there's a packet ready but the system, is busy
		// a completion port isn't a FIFO - leave the packt alone
		// wait for idle, then remove the packet
		PortWaitIdle();
		COMPLETION_WAITER waiter(Current);
		waiter.Stop( waiter_list, timeout );
		//if (queue.empty() && IsLinked())
			//waiting_thread_ports.unlink( this );
		packet = waiter.GetPacket();
	}
	else
	{
		// there's enough free threads to run, and there's a packet waiting
		// we're ready to go
		queue.Unlink( packet );
	}
	if (!packet)
		return STATUS_TIMEOUT;

	key = packet->key;
	value = packet->value;
	status = packet->status;
	info = packet->info;

	delete packet;

	return STATUS_SUCCESS;
}