size_t
ldns_rr_dnskey_key_size_raw(const unsigned char* keydata,
                            const size_t len,
                            const ldns_algorithm alg)
{
	/* for DSA keys */
	uint8_t t;
	
	/* for RSA keys */
	uint16_t exp;
	uint16_t int16;
	
	switch ((ldns_signing_algorithm)alg) {
	case LDNS_SIGN_DSA:
	case LDNS_SIGN_DSA_NSEC3:
		if (len > 0) {
			t = keydata[0];
			return (64 + t*8)*8;
		} else {
			return 0;
		}
		break;
	case LDNS_SIGN_RSAMD5:
	case LDNS_SIGN_RSASHA1:
	case LDNS_SIGN_RSASHA1_NSEC3:
#ifdef USE_SHA2
	case LDNS_SIGN_RSASHA256:
	case LDNS_SIGN_RSASHA512:
#endif
		if (len > 0) {
			if (keydata[0] == 0) {
				/* big exponent */
				if (len > 3) {
					memmove(&int16, keydata + 1, 2);
					exp = ntohs(int16);
					return (len - exp - 3)*8;
				} else {
					return 0;
				}
			} else {
				exp = keydata[0];
				return (len-exp-1)*8;
			}
		} else {
			return 0;
		}
		break;
#ifdef USE_GOST
	case LDNS_SIGN_ECC_GOST:
		return 512;
#endif
#ifdef USE_ECDSA
        case LDNS_SIGN_ECDSAP256SHA256:
                return 256;
        case LDNS_SIGN_ECDSAP384SHA384:
                return 384;
#endif
	case LDNS_SIGN_HMACMD5:
		return len;
	default:
		return 0;
	}
}