void
ProcessInterfaceWatchNotify(int s)
{
	char buffer[4096];
	struct iovec iov;
	struct msghdr hdr;
	struct nlmsghdr *nlhdr;
	struct ifinfomsg *ifi;
	struct ifaddrmsg *ifa;
	int len;

	struct rtattr *rth; //
	int rtl;

	unsigned int ext_if_name_index = 0;

	iov.iov_base = buffer;
	iov.iov_len = sizeof(buffer);

	memset(&hdr, 0, sizeof(hdr));
	hdr.msg_iov = &iov;
	hdr.msg_iovlen = 1;

	len = recvmsg(s, &hdr, 0);
	if (len < 0)
	{
		syslog(LOG_ERR, "recvmsg(s, &hdr, 0): %m");
		return;
	}

	if(ext_if_name) {
		ext_if_name_index = if_nametoindex(ext_if_name);
	}

	for (nlhdr = (struct nlmsghdr *) buffer;
	     NLMSG_OK (nlhdr, (unsigned int)len);
	     nlhdr = NLMSG_NEXT (nlhdr, len))
	{
		if (nlhdr->nlmsg_type == NLMSG_DONE)
			break;
		switch(nlhdr->nlmsg_type) {
		case RTM_DELLINK:
			ifi = (struct ifinfomsg *) NLMSG_DATA(nlhdr);
			/*if (ProcessInterfaceDown(ifi) < 0)
				syslog(LOG_ERR, "ProcessInterfaceDown(ifi) failed");*/
			break;
		case RTM_NEWLINK:
			ifi = (struct ifinfomsg *) NLMSG_DATA(nlhdr);
			/*if (ProcessInterfaceUp(ifi) < 0)
				syslog(LOG_ERR, "ProcessInterfaceUp(ifi) failed");*/
			break;
		case RTM_NEWADDR:
			/* see /usr/include/linux/netlink.h
			 * and /usr/include/linux/rtnetlink.h */
			ifa = (struct ifaddrmsg *) NLMSG_DATA(nlhdr);
			syslog(LOG_DEBUG, "ProcessInterfaceWatchNotify RTM_NEWADDR");
			for(rth = IFA_RTA(ifa), rtl = IFA_PAYLOAD(nlhdr);
			    rtl && RTA_OK(rth, rtl);
			    rth = RTA_NEXT(rth, rtl)) {
				syslog(LOG_DEBUG, " - %u - %s type=%d",
				       ifa->ifa_index, inet_ntoa(*((struct in_addr *)RTA_DATA(rth))),
				       rth->rta_type);
			}
			if(ifa->ifa_index == ext_if_name_index) {
				should_send_public_address_change_notif = 1;
			}
			break;
		case RTM_DELADDR:
			ifa = (struct ifaddrmsg *) NLMSG_DATA(nlhdr);
			syslog(LOG_DEBUG, "ProcessInterfaceWatchNotify RTM_DELADDR");
			if(ifa->ifa_index == ext_if_name_index) {
				should_send_public_address_change_notif = 1;
			}
			break;
		default:
			syslog(LOG_DEBUG, "ProcessInterfaceWatchNotify type %d ignored", nlhdr->nlmsg_type);
		}
	}

}