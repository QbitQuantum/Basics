/*
 *	make_trans -- Construct a single transform payload
 *
 *	Inputs:
 *
 *	length	(output) length of entire transform payload.
 *	next    Next Payload Type (3 = More transforms; 0=No more transforms)
 *	number	Transform number
 *	cipher	The encryption algorithm
 *	keylen	Key length for variable length keys (0=fixed key length)
 *	hash	Hash algorithm
 *	auth	Authentication method
 *	group	DH Group number
 *	lifetime	Lifetime in seconds (0=no lifetime)
 *	lifesize	Life in kilobytes (0=no life)
 *
 *	Returns:
 *
 *	Pointer to transform payload.
 *
 *	This constructs a single transform payload.
 *	Most of the values are defined in RFC 2409 Appendix A.
 */
unsigned char*make_trans(size_t *length, unsigned next, unsigned number,
			 unsigned cipher,
			 unsigned keylen, unsigned hash, unsigned auth,
			 unsigned group,
			 unsigned lifetime, unsigned lifesize, int gss_id_flag,
			 unsigned char *gss_data, size_t gss_data_len)
{

	struct isakmp_transform* hdr;   /* Transform header */
	unsigned char *payload;
	unsigned char *attr;
	unsigned char *cp;
	size_t attr_len;                /* Attribute Length */
	size_t len;                     /* Payload Length */

/* Allocate and initialise the transform header */

	hdr = Malloc(sizeof(struct isakmp_transform));
	memset(hdr, '\0', sizeof(struct isakmp_transform));

	hdr->isat_np = next;            /* Next payload type */
	hdr->isat_transnum = number;    /* Transform Number */
	hdr->isat_transid = KEY_IKE;

/* Allocate and initialise the mandatory attributes */

	add_attr(0, NULL, 'B', OAKLEY_ENCRYPTION_ALGORITHM, 0, cipher, NULL);
	add_attr(0, NULL, 'B', OAKLEY_HASH_ALGORITHM, 0, hash, NULL);
	add_attr(0, NULL, 'B', OAKLEY_AUTHENTICATION_METHOD, 0, auth, NULL);
	add_attr(0, NULL, 'B', OAKLEY_GROUP_DESCRIPTION, 0, group, NULL);

/* Allocate and initialise the optional attributes */

	if (keylen)
		add_attr(0, NULL, 'B', OAKLEY_KEY_LENGTH, 0, keylen, NULL);

	if (lifetime) {
		uint32_t lifetime_n = htonl(lifetime);

		add_attr(0, NULL, 'B', OAKLEY_LIFE_TYPE, 0,
			 SA_LIFE_TYPE_SECONDS, NULL);
		add_attr(0, NULL, 'V', OAKLEY_LIFE_DURATION, 4, 0,
			 &lifetime_n);
	}

	if (lifesize) {
		uint32_t lifesize_n = htonl(lifesize);

		add_attr(0, NULL, 'B', OAKLEY_LIFE_TYPE, 0,
			 SA_LIFE_TYPE_KBYTES, NULL);
		add_attr(0, NULL, 'V', OAKLEY_LIFE_DURATION, 4, 0,
			 &lifesize_n);
	}

	if (gss_id_flag)
		add_attr(0, NULL, 'V', OAKLEY_GSS_ID, gss_data_len, 0,
			 gss_data);

/* Finalise attributes and fill in length value */

	attr = add_attr(1, &attr_len, '\0', 0, 0, 0, NULL);
	len = attr_len + sizeof(struct isakmp_transform);
	hdr->isat_length = htons(len);  /* Transform length */
	*length = len;

/* Allocate memory for payload and copy structures to payload */

	payload = Malloc(len);

	cp = payload;
	memcpy(cp, hdr, sizeof(struct isakmp_transform));
	free(hdr);
	cp += sizeof(struct isakmp_transform);
	memcpy(cp, attr, attr_len);
	free(attr);

	return payload;
}