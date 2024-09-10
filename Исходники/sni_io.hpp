	void Push( __out_opt SNI_Packet *pPacket)
	{
		if( QueryDepthSList(&m_SListHeader) < MAX_PACKET_CACHE_SIZE - 1 )
		{
			SLIST_ENTRY* pEntry = static_cast<SLIST_ENTRY*>(SNIPacketGetDescriptor(pPacket));
			InterlockedPushEntrySList(&m_SListHeader, pEntry);
		}
		else
		{
			// Strategy: Don't make an effort to clean up the "extra" entries, but don't push this one onto the stack
			// if it will go over. This guarantees an *approximate* maximum 
			// (bounded above by MAX_PACKET_CACHE_SIZE + ConcurrentThreadsAccessingTheStack)
			
			// It would cost a lot of performance to put a stronger guarantee on the maximal size, since
			// we would need to synchronize access to two variables (stack head, stack size), which we 
			// don't know how to do without using a true [....] primitive, rather than the two separate
			// Interlocked operations which are all that's required to maintain consistency of the list header and 
			// an *approximate* depth guarantee.
			SNIPacketDelete(pPacket);
		}
	}