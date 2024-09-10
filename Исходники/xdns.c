static struct mxlist_t *my_get_mx_list2(struct sockaddr_in *dns_addr, const char *domain, int *err_stat)
{
	int sock, reply_len, rrcode, buf_size;
	int loc_retry;
	struct timeval tv;
	struct fd_set fds;
	unsigned char *buf;
	unsigned short query_fl;
	struct dnsreq_t *reply_hdr;
	struct mx_rrlist_t *rrlist=NULL, *rr1;
	struct mxlist_t *mxlist_root, *mxlist_top, *mxlist_new;

	*err_stat = 1;

	buf_size = 4096;
	buf = (char *)mx_alloc(buf_size);
	if (buf == NULL) return NULL;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == 0 || sock == INVALID_SOCKET) {
		mx_free(buf);
		return NULL;
	}

	for (loc_retry=0; loc_retry<2; loc_retry++) {
		mxlist_root = mxlist_top = NULL;

		if (loc_retry == 0)
			query_fl = htons(0x0100);
		else
			query_fl = htons(0);

		if (mx_make_query(sock, dns_addr, domain, query_fl))
			continue;

		FD_ZERO(&fds); FD_SET(sock, &fds);
		tv.tv_sec = 12; tv.tv_usec = 0;
		if (select(0, &fds, NULL, NULL, &tv) <= 0)
			continue;

		memset(buf, '\0', sizeof(buf));
		reply_len = recv(sock, buf, buf_size,0);
		if (reply_len <= 0 || reply_len <= sizeof(struct dnsreq_t))
			continue;

		reply_hdr = (struct dnsreq_t *)buf;

		rrcode = ntohs(reply_hdr->flags) & 0x0F;
		if (rrcode == 3) {
			*err_stat = 2;
			break;
		}
		if ((rrcode == 2) && (ntohs(reply_hdr->flags) & 0x80)) {
			*err_stat = 2;
			break;
		}
		if (rrcode != 0)
			continue;

		rrlist = mx_parse_rr(buf, reply_len);
		if (rrlist == NULL)
			continue;

		mxlist_root = mxlist_top = NULL;
		for (rr1=rrlist; rr1; rr1=rr1->next) {
			if ((rr1->rr_class != CLASS_IN) || (rr1->rr_type != TYPE_MX) || (rr1->rdlen < 3))
				continue;
			mxlist_new = (struct mxlist_t *)mx_alloc(sizeof(struct mxlist_t));
			if (mxlist_new == NULL) break;
			memset(mxlist_new, 0, sizeof(struct mxlist_t));

			mxlist_new->pref = ntohs(*(WORD *)(buf+rr1->rdata_offs+0));
			mx_decode_domain(buf, rr1->rdata_offs+2, reply_len, mxlist_new->mx);
			if (mxlist_new->mx[0] == 0) {
				mx_free(mxlist_new);
				continue;
			}

			if (mxlist_top == NULL) {
				mxlist_root = mxlist_top = mxlist_new;
			} else {
				mxlist_top->next = mxlist_new;
				mxlist_top = mxlist_new;
			}
		}

		if (mxlist_root == NULL) {
			mx_free_rrlist(rrlist);
			continue;
		}

		mx_free_rrlist(rrlist);
		break;
	}
	mx_free(buf);
	closesocket(sock);
	return mxlist_root;
}