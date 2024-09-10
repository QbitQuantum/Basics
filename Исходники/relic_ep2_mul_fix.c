void ep2_mul_fix_yaowi(ep2_t r, ep2_t *t, bn_t k) {
	int i, j, l;
	ep2_t a;
	uint8_t win[CEIL(2 * FP_BITS, EP_DEPTH)];

	ep2_null(a);

	TRY {
		ep2_new(a);

		ep2_set_infty(r);
		ep2_set_infty(a);

		l = CEIL(2 * FP_BITS, EP_DEPTH);
		bn_rec_win(win, &l, k, EP_DEPTH);

		for (j = (1 << EP_DEPTH) - 1; j >= 1; j--) {
			for (i = 0; i < l; i++) {
				if (win[i] == j) {
					ep2_add(a, a, t[i]);
				}
			}
			ep2_add(r, r, a);
		}
		ep2_norm(r, r);
	}
	CATCH_ANY {
		THROW(ERR_CAUGHT);
	}
	FINALLY {
		ep2_free(a);
	}
}