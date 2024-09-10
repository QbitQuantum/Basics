/*
 * Poll for the completion of non-blocking connect().
 * If there's a completion, the function return the key of the completed
 * socket, and 'result' argument contains the connect() result. If connect()
 * succeeded, 'result' will have value zero, otherwise will have the error
 * code.
 */
static int check_connecting( pj_ioqueue_t *ioqueue )
{
    if (ioqueue->connecting_count) {
	int i, count;
	struct 
	{
	    pj_ioqueue_key_t *key;
	    pj_status_t	      status;
	} events[PJ_IOQUEUE_MAX_EVENTS_IN_SINGLE_POLL-1];

	pj_lock_acquire(ioqueue->lock);
	for (count=0; count<PJ_IOQUEUE_MAX_EVENTS_IN_SINGLE_POLL-1; ++count) {
	    DWORD result;

	    result = WaitForMultipleObjects(ioqueue->connecting_count,
					    ioqueue->connecting_handles,
					    FALSE, 0);
	    if (result >= WAIT_OBJECT_0 && 
		result < WAIT_OBJECT_0+ioqueue->connecting_count) 
	    {
		WSANETWORKEVENTS net_events;

		/* Got completed connect(). */
		unsigned pos = result - WAIT_OBJECT_0;
		events[count].key = ioqueue->connecting_keys[pos];

		/* See whether connect has succeeded. */
		WSAEnumNetworkEvents((pj_sock_t)events[count].key->hnd, 
				     ioqueue->connecting_handles[pos], 
				     &net_events);
		events[count].status = 
		    PJ_STATUS_FROM_OS(net_events.iErrorCode[FD_CONNECT_BIT]);

		/* Erase socket from pending connect. */
		erase_connecting_socket(ioqueue, pos);
	    } else {
		/* No more events */
		break;
	    }
	}
	pj_lock_release(ioqueue->lock);

	/* Call callbacks. */
	for (i=0; i<count; ++i) {
	    if (events[i].key->cb.on_connect_complete) {
		events[i].key->cb.on_connect_complete(events[i].key, 
						      events[i].status);
	    }
	}

	return count;
    }

    return 0;
    
}