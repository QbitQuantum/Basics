int main(void)
{
	int sfd, n;
	char buf[1024];
	usr_t *p;
	socklen_t len;
	struct sockaddr_in cli_addr;

	get_usr_info("usr_info.txt");
	sfd = sock_init(8000, "127.0.0.1");

	while (1) {
		len = sizeof(struct sockaddr_in);
		n = recvfrom(sfd, buf, 1024, 0,
				(struct sockaddr *)&cli_addr, &len);
		buf[n] = '\0';

		if (strncmp(buf, "syn", 3) == 0) { /* login */
			char *name;

			name = strstr(buf, " ");		/* 客户端数据格式 "syn usr_name"*/
			name++;
			p = search_by_name(name);
			if (p == NULL)
				sendto(sfd, "fail", strlen("fail"), 0,
						(struct sockaddr *)&cli_addr,
						sizeof(cli_addr));
			else {
				p->is_online = 1;
				p->addr = cli_addr;
				sendto(sfd, "OK", strlen("OK"), 0,
						(struct sockaddr *)&cli_addr,
						sizeof(cli_addr));
			}
#ifdef DEBUG
			print();
#endif
		} else if (strncmp(buf, "fin", 3) == 0) {/* logout */
			char *name;

			name = strstr(buf, " ");
			name++;
			p = search_by_name(name);
			if (p == NULL)
				sendto(sfd, "fail", strlen("fail"), 0,
						(struct sockaddr *)&cli_addr,
						sizeof(cli_addr));
			else {
				p->is_online = 0;
				memset(&p->addr, 0, sizeof(p->addr));
				sendto(sfd, "OK", strlen("OK"), 0,
						(struct sockaddr *)&cli_addr,
						sizeof(cli_addr));
			}
#ifdef DEBUG
			print();
#endif
		} else {					   	/* somebody talk */
			char msg[32];

			p = search_by_addr(&cli_addr);
			if (p == NULL)
				continue;

			sprintf(msg, "%s say: ", p->usr_name);
			for (p = head; p != NULL; p = p->next) {		/* 广播 */
				if (p->is_online) {						
					n = sendto(sfd, msg, strlen(msg), 0,
							(struct sockaddr *)&p->addr, 
							sizeof(p->addr));
					n = sendto(sfd, buf, strlen(buf), 0,
							(struct sockaddr *)&p->addr,
							sizeof(p->addr));
				}
			}
		}
		printf("one data over...\n");
	}

	destroy();

	return 0;
}