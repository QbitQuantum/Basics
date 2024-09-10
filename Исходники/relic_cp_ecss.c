int cp_ecss_sig(bn_t e, bn_t s, uint8_t *msg, int len, bn_t d) {
	bn_t n, k, x, r;
	ec_t p;
	uint8_t hash[MD_LEN];
	uint8_t m[len + FC_BYTES];
	int result = STS_OK;

	bn_null(n);
	bn_null(k);
	bn_null(x);
	bn_null(r);
	ec_null(p);

	TRY {
		bn_new(n);
		bn_new(k);
		bn_new(x);
		bn_new(r);
		ec_new(p);

		ec_curve_get_ord(n);
		do {
			bn_rand_mod(k, n);
			ec_mul_gen(p, k);
			ec_get_x(x, p);
			bn_mod(r, x, n);
		} while (bn_is_zero(r));

		memcpy(m, msg, len);
		bn_write_bin(m + len, FC_BYTES, r);
		md_map(hash, m, len + FC_BYTES);

		if (8 * MD_LEN > bn_bits(n)) {
			len = CEIL(bn_bits(n), 8);
			bn_read_bin(e, hash, len);
			bn_rsh(e, e, 8 * MD_LEN - bn_bits(n));
		} else {
			bn_read_bin(e, hash, MD_LEN);
		}

		bn_mod(e, e, n);

		bn_mul(s, d, e);
		bn_mod(s, s, n);
		bn_sub(s, n, s);
		bn_add(s, s, k);
		bn_mod(s, s, n);
	}
	CATCH_ANY {
		result = STS_ERR;
	}
	FINALLY {
		bn_free(n);
		bn_free(k);
		bn_free(x);
		bn_free(r);
		ec_free(p);
	}
	return result;
}