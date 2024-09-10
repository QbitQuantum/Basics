void
lp_rast_triangle_3_4(struct lp_rasterizer_task *task,
                     const union lp_rast_cmd_arg arg)
{
   const struct lp_rast_triangle *tri = arg.triangle.tri;
   const struct lp_rast_plane *plane = GET_PLANES(tri);
   unsigned x = (arg.triangle.plane_mask & 0xff) + task->x;
   unsigned y = (arg.triangle.plane_mask >> 8) + task->y;

   __m128i p0 = _mm_load_si128((__m128i *)&plane[0]); /* c, dcdx, dcdy, eo */
   __m128i p1 = _mm_load_si128((__m128i *)&plane[1]); /* c, dcdx, dcdy, eo */
   __m128i p2 = _mm_load_si128((__m128i *)&plane[2]); /* c, dcdx, dcdy, eo */
   __m128i zero = _mm_setzero_si128();

   __m128i c;
   __m128i dcdx;
   __m128i dcdy;

   __m128i dcdx2;
   __m128i dcdx3;
   
   __m128i span_0;                /* 0,dcdx,2dcdx,3dcdx for plane 0 */
   __m128i span_1;                /* 0,dcdx,2dcdx,3dcdx for plane 1 */
   __m128i span_2;                /* 0,dcdx,2dcdx,3dcdx for plane 2 */
   __m128i unused;

   transpose4_epi32(&p0, &p1, &p2, &zero,
                    &c, &dcdx, &dcdy, &unused);

   /* Adjust dcdx;
    */
   dcdx = _mm_sub_epi32(zero, dcdx);

   c = _mm_add_epi32(c, mm_mullo_epi32(dcdx, _mm_set1_epi32(x)));
   c = _mm_add_epi32(c, mm_mullo_epi32(dcdy, _mm_set1_epi32(y)));

   /* Adjust so we can just check the sign bit (< 0 comparison), instead of having to do a less efficient <= 0 comparison */
   c = _mm_sub_epi32(c, _mm_set1_epi32(1));

   dcdx2 = _mm_add_epi32(dcdx, dcdx);
   dcdx3 = _mm_add_epi32(dcdx2, dcdx);

   transpose4_epi32(&zero, &dcdx, &dcdx2, &dcdx3,
                    &span_0, &span_1, &span_2, &unused);


   {
      __m128i c0_0 = _mm_add_epi32(SCALAR_EPI32(c, 0), span_0);
      __m128i c1_0 = _mm_add_epi32(SCALAR_EPI32(c, 1), span_1);
      __m128i c2_0 = _mm_add_epi32(SCALAR_EPI32(c, 2), span_2);
      
      __m128i c_0 = _mm_or_si128(_mm_or_si128(c0_0, c1_0), c2_0);

      __m128i c0_1 = _mm_add_epi32(c0_0, SCALAR_EPI32(dcdy, 0));
      __m128i c1_1 = _mm_add_epi32(c1_0, SCALAR_EPI32(dcdy, 1));
      __m128i c2_1 = _mm_add_epi32(c2_0, SCALAR_EPI32(dcdy, 2));

      __m128i c_1 = _mm_or_si128(_mm_or_si128(c0_1, c1_1), c2_1);
      __m128i c_01 = _mm_packs_epi32(c_0, c_1);

      __m128i c0_2 = _mm_add_epi32(c0_1, SCALAR_EPI32(dcdy, 0));
      __m128i c1_2 = _mm_add_epi32(c1_1, SCALAR_EPI32(dcdy, 1));
      __m128i c2_2 = _mm_add_epi32(c2_1, SCALAR_EPI32(dcdy, 2));

      __m128i c_2 = _mm_or_si128(_mm_or_si128(c0_2, c1_2), c2_2);

      __m128i c0_3 = _mm_add_epi32(c0_2, SCALAR_EPI32(dcdy, 0));
      __m128i c1_3 = _mm_add_epi32(c1_2, SCALAR_EPI32(dcdy, 1));
      __m128i c2_3 = _mm_add_epi32(c2_2, SCALAR_EPI32(dcdy, 2));

      __m128i c_3 = _mm_or_si128(_mm_or_si128(c0_3, c1_3), c2_3);
      __m128i c_23 = _mm_packs_epi32(c_2, c_3);
      __m128i c_0123 = _mm_packs_epi16(c_01, c_23);

      unsigned mask = _mm_movemask_epi8(c_0123);

      if (mask != 0xffff)
         lp_rast_shade_quads_mask(task,
                                  &tri->inputs,
                                  x,
                                  y,
                                  0xffff & ~mask);
   }
}