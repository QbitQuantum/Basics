static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	char fmt[4096], num[128];
	int rv, rescount = -1;
	int bufi, numi;
	char *res, *r;
	if (!fd || !fd->data) {
		return -1;
	}
	if (count > 1024) {
		count = 1024;
	}
	snprintf (fmt, sizeof (fmt),
		"{\"op\":\"read\",\"address\":%"PFMT64d",\"count\":%d}",
		io->off, count);
	rv = r2p_write (R2P (fd), fmt);
	if (rv < 1) {
		eprintf ("r2p_write: error\n");
		return -1;
	}
	res = r2p_read (R2P (fd));

	/* TODO: parse json back */
	r = strstr (res, "result");
	if (r) {
		rescount = atoi (r + 6 + 2);
	}
	r = strstr (res, "data");
	if (r) {
		char *arr = strchr (r, ':');
		if (!arr || arr[1]!='[') {
			goto beach;
		}
		arr += 2;
		for (num[0] = numi = bufi = 0; bufi < count && *arr; arr++) {
			switch (*arr) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				num[numi++] = *arr;
				num[numi] = 0;
				break;
			case ' ':
			case ',':
			case ']':
				if (num[0]) {
					buf[bufi++] = atoi (num);
					num[numi = 0] = 0;
				}
				break;
			case 'n':
			case 'u':
			case 'l':
				break;
			default:
				goto beach;
				break;
			}
		}
	}
beach:
	free (res);
	return rescount;
}