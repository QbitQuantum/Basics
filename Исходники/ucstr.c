/* slow, should be optimized */
int UTF8bvnormcmp(
	struct berval *bv1,
	struct berval *bv2,
	unsigned flags,
	void *ctx )
{
	int i, l1, l2, len, ulen, res = 0;
	char *s1, *s2, *done;
	ac_uint4 *ucs, *ucsout1, *ucsout2;

	unsigned casefold = flags & LDAP_UTF8_CASEFOLD;
	unsigned norm1 = flags & LDAP_UTF8_ARG1NFC;
	unsigned norm2 = flags & LDAP_UTF8_ARG2NFC;

	if (bv1 == NULL) {
		return bv2 == NULL ? 0 : -1;

	} else if (bv2 == NULL) {
		return 1;
	}

	l1 = bv1->bv_len;
	l2 = bv2->bv_len;

	len = (l1 < l2) ? l1 : l2;
	if (len == 0) {
		return l1 == 0 ? (l2 == 0 ? 0 : -1) : 1;
	}

	s1 = bv1->bv_val;
	s2 = bv2->bv_val;
	done = s1 + len;

	while ( (s1 < done) && LDAP_UTF8_ISASCII(s1) && LDAP_UTF8_ISASCII(s2) ) {
		if (casefold) {
			char c1 = TOLOWER(*s1);
			char c2 = TOLOWER(*s2);
			res = c1 - c2;
		} else {
			res = *s1 - *s2;
		}			
		s1++;
		s2++;
		if (res) {
			/* done unless next character in s1 or s2 is non-ascii */
			if (s1 < done) {
				if (!LDAP_UTF8_ISASCII(s1) || !LDAP_UTF8_ISASCII(s2)) {
					break;
				}
			} else if (((len < l1) && !LDAP_UTF8_ISASCII(s1)) ||
				((len < l2) && !LDAP_UTF8_ISASCII(s2)))
			{
				break;
			}
			return res;
		}
	}

	/* We have encountered non-ascii or strings equal up to len */

	/* set i to number of iterations */
	i = s1 - done + len;
	/* passed through loop at least once? */
	if (i > 0) {
		if (!res && (s1 == done) &&
		    ((len == l1) || LDAP_UTF8_ISASCII(s1)) &&
		    ((len == l2) || LDAP_UTF8_ISASCII(s2))) {
			/* all ascii and equal up to len */
			return l1 - l2;
		}

		/* rewind one char, and do normalized compare from there */
		s1--;
		s2--;
		l1 -= i - 1;
		l2 -= i - 1;
	}
			
	/* Should first check to see if strings are already in
	 * proper normalized form.
	 */
	ucs = malloc( ( ( norm1 || l1 > l2 ) ? l1 : l2 ) * sizeof(*ucs) );
	if ( ucs == NULL ) {
		return l1 > l2 ? 1 : -1; /* what to do??? */
	}
	
	/*
	 * XXYYZ: we convert to ucs4 even though -llunicode
	 * expects ucs2 in an ac_uint4
	 */
	
	/* convert and normalize 1st string */
	for ( i = 0, ulen = 0; i < l1; i += len, ulen++ ) {
		ucs[ulen] = ldap_x_utf8_to_ucs4( s1 + i );
		if ( ucs[ulen] == LDAP_UCS4_INVALID ) {
			free( ucs );
			return -1; /* what to do??? */
		}
		len = LDAP_UTF8_CHARLEN( s1 + i );
	}

	if ( norm1 ) {
		ucsout1 = ucs;
		l1 = ulen;
		ucs = malloc( l2 * sizeof(*ucs) );
		if ( ucs == NULL ) {
			free( ucsout1 );
			return l1 > l2 ? 1 : -1; /* what to do??? */
		}
	} else {
		uccompatdecomp( ucs, ulen, &ucsout1, &l1, ctx );
		l1 = uccanoncomp( ucsout1, l1 );
	}

	/* convert and normalize 2nd string */
	for ( i = 0, ulen = 0; i < l2; i += len, ulen++ ) {
		ucs[ulen] = ldap_x_utf8_to_ucs4( s2 + i );
		if ( ucs[ulen] == LDAP_UCS4_INVALID ) {
			free( ucsout1 );
			free( ucs );
			return 1; /* what to do??? */
		}
		len = LDAP_UTF8_CHARLEN( s2 + i );
	}

	if ( norm2 ) {
		ucsout2 = ucs;
		l2 = ulen;
	} else {
		uccompatdecomp( ucs, ulen, &ucsout2, &l2, ctx );
		l2 = uccanoncomp( ucsout2, l2 );
		free( ucs );
	}
	
	res = casefold
		? ucstrncasecmp( ucsout1, ucsout2, l1 < l2 ? l1 : l2 )
		: ucstrncmp( ucsout1, ucsout2, l1 < l2 ? l1 : l2 );
	free( ucsout1 );
	free( ucsout2 );

	if ( res != 0 ) {
		return res;
	}
	if ( l1 == l2 ) {
		return 0;
	}
	return l1 > l2 ? 1 : -1;
}