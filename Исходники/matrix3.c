void matrix3_transpose(struct matrix3 *dst, const struct matrix3 *m)
{
	__m128 tmp1, tmp2;
	vec3_transform(&dst->t, &m->t, m);
	vec3_neg(&dst->t, &dst->t);

        tmp1 = _mm_movelh_ps(m->x.m, m->y.m);
        tmp2 = _mm_movehl_ps(m->y.m, m->x.m);
        dst->x.m = _mm_shuffle_ps(tmp1, m->z.m, _MM_SHUFFLE(3, 0, 2, 0));
        dst->y.m = _mm_shuffle_ps(tmp1, m->z.m, _MM_SHUFFLE(3, 1, 3, 1));
        dst->z.m = _mm_shuffle_ps(tmp2, m->z.m, _MM_SHUFFLE(3, 2, 2, 0));
}