void Print_getaddrinfo_list(struct addrinfo *list_head) {
	struct addrinfo *p = list_head;
	char info[MAXSTR];
	char tmpstr[MAXSTR];
	err_msg ("(%s) listing all results of getaddrinfo", prog_name);	
	while (p != NULL) {
		info[0]='\0';

		int ai_family = p->ai_family;
		if (ai_family == AF_INET)
			strcat(info, "AF_INET  ");
		else if (ai_family == AF_INET6)
			strcat(info, "AF_INET6 ");
		else
			{ sprintf(tmpstr, "(fam=%d?) ",ai_family); strcat(info, tmpstr); }

		int ai_socktype = p->ai_socktype;
		if (ai_socktype == SOCK_STREAM)
			strcat(info, "SOCK_STREAM ");
		else if (ai_socktype == SOCK_DGRAM)
			strcat(info, "SOCK_DGRAM  ");
		else if (ai_socktype == SOCK_RAW)
			strcat(info, "SOCK_RAW    ");
		else
			{ sprintf(tmpstr, "(sock=%d?) ",ai_socktype); strcat(info, tmpstr); }

		int ai_protocol = p->ai_protocol;
		if (ai_protocol == IPPROTO_UDP)
			strcat(info, "IPPROTO_UDP ");
		else if (ai_protocol == IPPROTO_TCP)
			strcat(info, "IPPROTO_TCP ");
		else if (ai_protocol == IPPROTO_IP)
			strcat(info, "IPPROTO_IP  ");
		else
			{ sprintf(tmpstr, "(proto=%d?) ",ai_protocol); strcat(info, tmpstr); }

		char text_addr[INET6_ADDRSTRLEN];
		if (ai_family == AF_INET)
			Inet_ntop(ai_family, &(((struct sockaddr_in *)p->ai_addr)->sin_addr), text_addr, sizeof(text_addr));
		else if (ai_family == AF_INET6)
			Inet_ntop(ai_family, &(((struct sockaddr_in6 *)p->ai_addr)->sin6_addr), text_addr, sizeof(text_addr));
		else
			strcpy(text_addr, "(addr=?)");
		//Inet_ntop(AF_INET6, p->ai_addr, text_addr, sizeof(text_addr));
		strcat(info, text_addr);
		strcat(info, " ");

		if (p->ai_canonname != NULL) {
			strcat(info, p->ai_canonname);
			strcat(info, " ");
		}
			
		err_msg ("(%s) %s", prog_name, info);
		p = p->ai_next;
	}
}