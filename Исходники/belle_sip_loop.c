static unsigned int belle_sip_source_get_revents(belle_sip_source_t *s,belle_sip_pollfd_t *pfd){
	WSANETWORKEVENTS revents={0};
	int err;
	unsigned int ret=0;
	
	if (WaitForSingleObjectEx(s->fd,0,FALSE)==WAIT_OBJECT_0){
		if (s->sock!=(belle_sip_socket_t)-1){
			/*special treatments for windows sockets*/
			err=WSAEnumNetworkEvents(s->sock,s->fd,&revents);
			if (err!=0){
				belle_sip_error("WSAEnumNetworkEvents() failed: %s socket=%x",belle_sip_get_socket_error_string(),(unsigned int)s->sock);
				return 0;
			}
			if (revents.lNetworkEvents & FD_READ){
				ret|=BELLE_SIP_EVENT_READ;
			}
			if (revents.lNetworkEvents & FD_WRITE){
				ret|=BELLE_SIP_EVENT_WRITE;
			}
			s->armed_events=0;
		}else{
			ret=BELLE_SIP_EVENT_READ;
			ResetEvent(s->fd);
		}
	}
	return ret;
}