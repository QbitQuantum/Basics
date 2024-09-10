/*
**  For a given socket, reqister a request structure, a set of operations, 
**  a HTEventCallback function, and a priority. For this implementation, 
**  we allow only a single HTEventCallback function for all operations.
**  and the priority field is ignored.
*/
PUBLIC int HTEventList_register (SOCKET s, HTEventType type, HTEvent * event)
{
    int newset = 0;
    SockEvents * sockp;
    HTTRACE(THD_TRACE, "Event....... Register socket %d, request %p handler %p type %s at priority %d\n" _ 
		s _ (void *) event->request _ 
		(void *) event->cbf _ HTEvent_type2str(type) _ 
		(unsigned) event->priority);
    if (s==INVSOC || HTEvent_INDEX(type) >= HTEvent_TYPES)
	return 0;

    /*
    ** Insert socket into appropriate file descriptor set. We also make sure
    ** that it is registered in the global set.
    */
    HTTRACE(THD_TRACE, "Event....... Registering socket for %s\n" _ HTEvent_type2str(type));
    sockp = SockEvents_get(s, SockEvents_mayCreate);
    sockp->s = s;
    sockp->events[HTEvent_INDEX(type)] = event;
    newset = EventList_remaining(sockp);
#ifdef WWW_WIN_ASYNC
    if (WSAAsyncSelect(s, HTSocketWin, HTwinMsg, HTEvent_BITS(newset)) < 0) {
        HTTRACE(THD_TRACE, "Event....... WSAAsyncSelect returned `%s'!" _ HTErrnoString(socerrno));
	return HT_ERROR;
    }
#else /* WWW_WIN_ASYNC */
    FD_SET(s, FdArray+HTEvent_INDEX(type));

    HTTRACEDATA((char *) FdArray+HTEvent_INDEX(type), 8, "HTEventList_register: (s:%d)" _ s);

    if (s > MaxSock) {
	MaxSock = s ;
	HTTRACE(THD_TRACE, "Event....... New value for MaxSock is %d\n" _ MaxSock);
    }
#endif /* !WWW_WIN_ASYNC */

    /*
    **  If the timeout has been set (relative in millis) then we register 
    **  a new timeout for this event unless we already have a timer.
    */
    if (event->millis >= 0) {
	sockp->timeouts[HTEvent_INDEX(type)] =
	    HTTimer_new(sockp->timeouts[HTEvent_INDEX(type)],
			EventListTimerHandler, sockp, event->millis, YES, YES);
    }

    return HT_OK;
}