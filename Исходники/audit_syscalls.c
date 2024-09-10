/*
 * The audit system call. Trust what the user has sent down and save it
 * away in the audit file. User passes a complete audit record and its
 * length.  We will fill in the time stamp, check the header and the length
 * Put a trailer and a sequence token if policy requires.
 * In the future length might become size_t instead of an int.
 *
 * The call is valid whether or not AUDIT_PERZONE is set (think of
 * login to a zone).  When the local audit state (auk_auditstate) is
 * AUC_INIT_AUDIT, records are accepted even though auditd isn't
 * running.
 */
int
audit(caddr_t record, int length)
{
	char	c;
	int	count, l;
	token_t	*m, *n, *s, *ad;
	int	hdrlen, delta;
	adr_t	hadr;
	adr_t	sadr;
	int	size;	/* 0: 32 bit utility  1: 64 bit utility */
	int	host_len;
	size_t	zlen;
	au_kcontext_t	*kctx = GET_KCTX_PZ;

	/* if auditing not enabled, then don't generate an audit record */
	if (kctx->auk_auditstate != AUC_AUDITING &&
	    kctx->auk_auditstate != AUC_INIT_AUDIT)
		return (0);

	/* Only privileged processes can audit */
	if (secpolicy_audit_modify(CRED()) != 0)
		return (EPERM);

	/* Max user record size is 32K */
	if (length > AUDIT_REC_SIZE)
		return (E2BIG);

	/*
	 * The specified length must be at least as big as the smallest
	 * possible header token. Later after beginning to scan the
	 * header we'll determine the true minimum length according to
	 * the header type and attributes.
	 */
#define	AU_MIN_HEADER_LEN	(sizeof (char) + sizeof (int32_t) + \
	sizeof (char) + sizeof (short) + sizeof (short) + \
	(sizeof (int32_t) * 2))

	if (length < AU_MIN_HEADER_LEN)
		return (EINVAL);

	/* Read in user's audit record */
	count = length;
	m = n = s = ad = NULL;
	while (count) {
		m = au_getclr();
		if (!s)
			s = n = m;
		else {
			n->next_buf = m;
			n = m;
		}
		l = MIN(count, AU_BUFSIZE);
		if (copyin(record, memtod(m, caddr_t), (size_t)l)) {
			/* copyin failed release au_membuf */
			au_free_rec(s);
			return (EFAULT);
		}
		record += l;
		count -= l;
		m->len = (uchar_t)l;
	}

	/* Now attach the entire thing to ad */
	au_write((caddr_t *)&(ad), s);

	/* validate header token type. trust everything following it */
	adr_start(&hadr, memtod(s, char *));
	(void) adr_getchar(&hadr, &c);
	switch (c) {
	case AUT_HEADER32:
		/* size vers+event_ID+event_modifier fields */
		delta = 1 + 2 + 2;
		hdrlen = 1 + 4 + delta + (sizeof (int32_t) * 2);
		size = HEADER_SIZE32;
		break;

#ifdef _LP64
	case AUT_HEADER64:
		/* size vers+event_ID+event_modifier fields */
		delta = 1 + 2 + 2;
		hdrlen = 1 + 4 + delta + (sizeof (int64_t) * 2);
		size = HEADER_SIZE64;
		break;
#endif

	case AUT_HEADER32_EX:
		/*
		 * Skip over the length/version/type/mod fields and
		 * grab the host address type (length), then rewind.
		 * This is safe per the previous minimum length check.
		 */
		hadr.adr_now += 9;
		(void) adr_getint32(&hadr, &host_len);
		hadr.adr_now -= 9 + sizeof (int32_t);

		/* size: vers+event_ID+event_modifier+IP_type+IP_addr_array */
		delta = 1 + 2 + 2 + 4 + host_len;
		hdrlen = 1 + 4 + delta + (sizeof (int32_t) * 2);
		size = HEADER_SIZE32;
		break;

#ifdef _LP64
	case AUT_HEADER64_EX:
		/*
		 * Skip over the length/version/type/mod fields and grab
		 * the host address type (length), then rewind.
		 * This is safe per the previous minimum length check.
		 */
		hadr.adr_now += 9;
		(void) adr_getint32(&hadr, &host_len);
		hadr.adr_now -= 9 + sizeof (int32_t);

		/* size: vers+event_ID+event_modifier+IP_type+IP_addr_array */
		delta = 1 + 2 + 2 + 4 + host_len;
		hdrlen = 1 + 4 + delta + (sizeof (int64_t) * 2);
		size = HEADER_SIZE64;
		break;
#endif

	default:
		/* Header is wrong, reject message */
		au_free_rec(s);
		return (EINVAL);
	}

	if (length < hdrlen) {
		au_free_rec(s);
		return (0);
	}

	/* advance over header token length field */
	hadr.adr_now += 4;

	/* validate version */
	(void) adr_getchar(&hadr, &c);
	if (c != TOKEN_VERSION) {
		/* version is wrong, reject message */
		au_free_rec(s);
		return (EINVAL);
	}

	/* backup to header length field (including version field) */
	hadr.adr_now -= 5;

	/*
	 * add on the zonename token if policy AUDIT_ZONENAME is set
	 */
	if (kctx->auk_policy & AUDIT_ZONENAME) {
		zlen = au_zonename_length(NULL);
		if (zlen > 0) {
			length += zlen;
			m = au_to_zonename(zlen, NULL);
			(void) au_append_rec(ad, m, AU_PACK);
		}
	}
	/* Add an (optional) sequence token. NULL offset if none */
	if (kctx->auk_policy & AUDIT_SEQ) {
		/* get the sequnce token */
		m = au_to_seq();

		/* sequence token 5 bytes long */
		length += 5;

		/* link to audit record (i.e. don't pack the data) */
		(void) au_append_rec(ad, m, AU_LINK);

		/* advance to count field of token */
		adr_start(&sadr, memtod(m, char *));
		sadr.adr_now += 1;
	} else