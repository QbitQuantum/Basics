int
_start (int m, int c, struct msgbuf *buf, int bufcnt)
{
	void vpn_user_init (void *, char *, int);

	if (m != MSG_BUF)
		exitprocess (1);
	printf ("vpn (user) init\n");
	vpn_user_init (buf[0].base, buf[1].base, buf[1].len);
	if (restrict (16384, 8 * 16384)) { /* stack must be aligned to 16KiB */
		printf ("vpn restrict failed\n");
		exitprocess (1);
	}
	return 0;
}