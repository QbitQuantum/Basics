static inline void cidr_in6inc(void *a) {
#if BIGENDIAN == 0
	union {
		uint8_t *c;
		uint64_t *dw;
		void *p;
	} p_u;
	uint64_t dw;
#endif
	u128_t tmp;

#if BIGENDIAN == 0
	p_u.p=a;
	tmp.l=ntohll(*p_u.dw);
	p_u.dw++;
	tmp.u=ntohll(*p_u.dw);
#else
	memcpy(&tmp, a, sizeof(tmp));
#endif

#if BIGENDIAN == 0
	tmp.u++;
	if (tmp.u == 0ULL) {
		tmp.l++;
	}
#else
	tmp.l++;
	if (tmp.l == 0ULL) {
		tmp.u++;
	}
#endif


#if BIGENDIAN == 0
	dw=htonll(tmp.l);
	p_u.p=a;
	memcpy(p_u.p, &dw, sizeof(dw));
	p_u.dw++;
	dw=htonll(tmp.u);
	memcpy(p_u.p, &dw, sizeof(dw));
#else
	memcpy(a, &tmp, sizeof(tmp));
#endif

        return;
}