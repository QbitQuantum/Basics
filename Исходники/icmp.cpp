int icmp_check_replies(char *ipaddress, void **udata)
{
	for(request_list::iterator rit=ping_list.begin();rit!=ping_list.end();rit++)
	{
		if(WaitForSingleObject(rit->hEvent,0)==0) //handle is signaled, reply received.
		{
			if(IcmpParseReplies(rit->replyBuffer,rit->replyBufferSize)>0)
			{
				memcpy(ipaddress,rit->ipaddress,4);

				ping_list.remove(rit);

				return 1; //reply received
			}
			ResetEvent(rit->hEvent);
		}
		if(GetTickCount() >= (rit->sTick+rit->timeOut))
		{
			memcpy(ipaddress,rit->ipaddress,4);
			*udata = rit->userdata;

			ping_list.remove(rit);

			return 2; //timeout
		}
	}
	return 0;
}