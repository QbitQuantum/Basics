int
randomize_fd(int fd, int type, int unique, double denom)
{
	u_char *buf;
	u_int slen;
	u_long i, j, numnode, selected;
	struct rand_node *n, *prev;
	int bufleft, eof, fndstr, ret;
	size_t bufc, buflen;
	ssize_t len;

	rand_root = rand_tail = NULL;
	bufc = i = 0;
	bufleft = eof = fndstr = numnode = 0;

	if (type == RANDOM_TYPE_UNSET)
		type = RANDOM_TYPE_LINES;

	buflen = sizeof(u_char) * MAXBSIZE;
	buf = (u_char *)malloc(buflen);
	if (buf == NULL)
		err(1, "malloc");

	while (!eof) {
		/* Check to see if we have bits in the buffer */
		if (bufleft == 0) {
			len = read(fd, buf, buflen);
			if (len == -1)
				err(1, "read");
			else if (len == 0) {
				eof++;
				break;
			} else if ((size_t)len < buflen)
				buflen = (size_t)len;

			bufleft = (int)len;
		}

		/* Look for a newline */
		for (i = bufc; i <= buflen && bufleft >= 0; i++, bufleft--) {
			if (i == buflen) {
				if (fndstr) {
					if (!eof) {
						memmove(buf, &buf[bufc], i - bufc);
						i -= bufc;
						bufc = 0;
						len = read(fd, &buf[i], buflen - i);
						if (len == -1)
							err(1, "read");
						else if (len == 0) {
							eof++;
							break;
						} else if (len < (ssize_t)(buflen - i))
							buflen = i + (size_t)len;

						bufleft = (int)len;
						fndstr = 0;
					}
				} else {
					buflen *= 2;
					buf = (u_char *)realloc(buf, buflen);
					if (buf == NULL)
						err(1, "realloc");

					if (!eof) {
						len = read(fd, &buf[i], buflen - i);
						if (len == -1)
							err(1, "read");
						else if (len == 0) {
							eof++;
							break;
						} else if (len < (ssize_t)(buflen - i))
							buflen = i + (size_t)len;

						bufleft = (int)len;
					}

				}
			}

			if ((type == RANDOM_TYPE_LINES && buf[i] == '\n') ||
			    (type == RANDOM_TYPE_WORDS && isspace(buf[i])) ||
			    (eof && i == buflen - 1)) {
			make_token:
				if (numnode == RANDOM_MAX_PLUS1) {
					errno = EFBIG;
					err(1, "too many delimiters");
				}
				numnode++;
				n = rand_node_allocate();
				if (-1 != (int)i) {
					slen = i - (u_long)bufc;
					n->len = slen + 2;
					n->cp = (u_char *)malloc(slen + 2);
					if (n->cp == NULL)
						err(1, "malloc");

					memmove(n->cp, &buf[bufc], slen);
					n->cp[slen] = buf[i];
					n->cp[slen + 1] = '\0';
					bufc = i + 1;
				}
				rand_node_append(n);
				fndstr = 1;
			}
		}
	}

	(void)close(fd);

	/* Necessary evil to compensate for files that don't end with a newline */
	if (bufc != i) {
		i--;
		goto make_token;
	}

	for (i = numnode; i > 0; i--) {
		selected = random() % numnode;

		for (j = 0, prev = n = rand_root; n != NULL; j++, prev = n, n = n->next) {
			if (j == selected) {
				if (n->cp == NULL)
					break;

				if ((int)(denom * random() /
					RANDOM_MAX_PLUS1) == 0) {
					ret = printf("%.*s",
						(int)n->len - 1, n->cp);
					if (ret < 0)
						err(1, "printf");
				}
				if (unique) {
					if (n == rand_root)
						rand_root = n->next;
					if (n == rand_tail)
						rand_tail = prev;

					prev->next = n->next;
					rand_node_free(n);
					numnode--;
				}
				break;
			}
		}
	}

	fflush(stdout);

	if (!unique)
		rand_node_free_rec(rand_root);

	return(0);
}