static void recon8x8(int **m7, imgpel **mb_rec, imgpel **mpr, int max_imgpel_value, int ioff)
{
  int j;
  int    *m_tr  = NULL;
  imgpel *m_rec = NULL;
  imgpel *m_prd = NULL;
  __m128i mm_dq2 = _mm_set1_epi16((1<<(DQ_BITS_8-1)));
  __m128i mm0  = _mm_set1_epi16(0);
  __m128i mm7, mm72, mmPred, tmp;

  for( j = 0; j < 8; j++)
  {

	m_tr = (*m7++) + ioff;
    m_rec = (*mb_rec++) + ioff;
    m_prd = (*mpr++) + ioff;

	mm7 = _mm_loadu_si128((__m128i*) m_tr);
	mm72 = _mm_loadu_si128((__m128i*) (m_tr+4));
	mm7 = _mm_packs_epi32(mm7, mm72);

	mmPred = _mm_loadu_si128((__m128i*) m_prd);
	mmPred = _mm_unpacklo_epi8(mmPred, mm0);

	tmp = _mm_add_epi16(mm7, mm_dq2);
	tmp = _mm_srai_epi16(tmp, DQ_BITS_8);
	tmp = _mm_add_epi16(tmp, mmPred);

	tmp = _mm_packus_epi16(tmp, tmp);
	_mm_storel_epi64((__m128i*) m_rec, tmp);



	/*
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec++ = (imgpel) iClip1(max_imgpel_value, (*m_prd++) + rshift_rnd_sf(*m_tr++, DQ_BITS_8)); 
    *m_rec   = (imgpel) iClip1(max_imgpel_value, (*m_prd  ) + rshift_rnd_sf(*m_tr  , DQ_BITS_8)); 
	*/
  }
}