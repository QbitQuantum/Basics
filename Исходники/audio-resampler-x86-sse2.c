void
interpolate_gint16_cubic_sse2 (gpointer op, const gpointer ap,
    gint len, const gpointer icp, gint astride)
{
  gint i = 0;
  gint16 *o = op, *a = ap, *ic = icp;
  __m128i ta, tb, tl1, tl2, th1, th2;
  __m128i f[2];
  const gint16 *c[4] = { (gint16 *) ((gint8 *) a + 0 * astride),
    (gint16 *) ((gint8 *) a + 1 * astride),
    (gint16 *) ((gint8 *) a + 2 * astride),
    (gint16 *) ((gint8 *) a + 3 * astride)
  };

  f[0] = _mm_set_epi16 (ic[1], ic[0], ic[1], ic[0], ic[1], ic[0], ic[1], ic[0]);
  f[1] = _mm_set_epi16 (ic[3], ic[2], ic[3], ic[2], ic[3], ic[2], ic[3], ic[2]);

  for (; i < len; i += 8) {
    ta = _mm_load_si128 ((__m128i *) (c[0] + i));
    tb = _mm_load_si128 ((__m128i *) (c[1] + i));

    tl1 = _mm_madd_epi16 (_mm_unpacklo_epi16 (ta, tb), f[0]);
    th1 = _mm_madd_epi16 (_mm_unpackhi_epi16 (ta, tb), f[0]);

    ta = _mm_load_si128 ((__m128i *) (c[2] + i));
    tb = _mm_load_si128 ((__m128i *) (c[3] + i));

    tl2 = _mm_madd_epi16 (_mm_unpacklo_epi16 (ta, tb), f[1]);
    th2 = _mm_madd_epi16 (_mm_unpackhi_epi16 (ta, tb), f[1]);

    tl1 = _mm_add_epi32 (tl1, tl2);
    th1 = _mm_add_epi32 (th1, th2);

    tl1 = _mm_add_epi32 (tl1, _mm_set1_epi32 (1 << (PRECISION_S16 - 1)));
    th1 = _mm_add_epi32 (th1, _mm_set1_epi32 (1 << (PRECISION_S16 - 1)));

    tl1 = _mm_srai_epi32 (tl1, PRECISION_S16);
    th1 = _mm_srai_epi32 (th1, PRECISION_S16);

    tl1 = _mm_packs_epi32 (tl1, th1);
    _mm_store_si128 ((__m128i *) (o + i), tl1);
  }
}