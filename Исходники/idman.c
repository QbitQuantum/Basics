int
_start (int m, int c, struct msgbuf *buf, int bufcnt)
{
	int idman_user_init (void *, char *, int);
	void *tmp;

	if (m != MSG_BUF)
		exitprocess (1);
	printf ("idman (user) init\n");
	usleep_desc = msgopen ("usleep");
	if (usleep_desc < 0) {
		printf ("open usleep failed\n");
		exitprocess (1);
	}
	tmp = alloc (buf[0].len);
	memcpy (tmp, buf[0].base, buf[0].len);
	if (idman_user_init (tmp, buf[1].base, buf[1].len)) {
		printf ("idman init failed\n");
		exitprocess (1);
	}
	if (restrict (16384, 8 * 16384)) {
		printf ("idman restrict failed\n");
		exitprocess (1);
	}
	printf ("ready\n");
	return 0;
}