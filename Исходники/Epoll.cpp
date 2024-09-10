int epoll_close(int epfd)
{
	GUARD();
    if(epfd < 1 || ep_data.find(epfd) == ep_data.end())
        return ENOENT;

    ep_internal& epi = ep_data[epfd];
    for(ep_internal::size_type i = 0; i < epi.size(); ++i) {

		// now unset the event notifications
		WSAEventSelect(epi[i].fd, 0, 0);
		// clean up event
		WSACloseEvent(epi[i].wsa_event);
	}
    ep_data.erase(epfd);
    return 0;
}