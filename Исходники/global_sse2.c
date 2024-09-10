int
global_sse2_word(int                  queryLength,
                 unsigned short      *profile,
                 const unsigned char *dbSeq,
                 int                  dbLength,
                 unsigned short       gapOpen,
                 unsigned short       gapExtend,
                 unsigned short       ceiling,
                 struct f_struct     *f_str)
{
  int     i, j;

  int     score;
  int     scale;
  int     temp;
  int     distance;

  int     offset;
  int     position;

  int     cmp;
  int     iter;
    
  __m128i *pvH;
  __m128i *pvE;

  __m128i vE, vF, vH;
  __m128i vHNext;
  __m128i vFPrev;

  __m128i vGapOpen;
  __m128i vGapExtend;
  __m128i vCeiling;

  __m128i vScale;
  __m128i vScaleAmt;
  __m128i vScaleTmp;

  __m128i vTemp;
  __m128i vNull;

  __m128i *pvScore;

  scale = 0;
  iter = (queryLength + 7) / 8;
  offset = (queryLength - 1) % iter;
  position = 7 - (queryLength - 1) / iter;

  pvH = (__m128i *)f_str->workspace;
  pvE = pvH + iter;

  /* Load gap opening penalty to all elements of a constant */
  vGapOpen = _mm_setzero_si128();	/* transfered from Apple Devel smith_waterman_sse2.c fix */
  vGapOpen = _mm_insert_epi16 (vGapOpen, gapOpen, 0);
  vGapOpen = _mm_shufflelo_epi16 (vGapOpen, 0);
  vGapOpen = _mm_shuffle_epi32 (vGapOpen, 0);

  /* Load gap extension penalty to all elements of a constant */
  vGapExtend = _mm_setzero_si128();	/* transfered from Apple Devel smith_waterman_sse2.c fix */
  vGapExtend = _mm_insert_epi16 (vGapExtend, gapExtend, 0);
  vGapExtend = _mm_shufflelo_epi16 (vGapExtend, 0);
  vGapExtend = _mm_shuffle_epi32 (vGapExtend, 0);

  /* Generate the ceiling before scaling */
  vTemp = _mm_setzero_si128();	/* transfered from Apple Devel smith_waterman_sse2.c fix */
  vTemp = _mm_insert_epi16 (vTemp, ceiling, 0);
  vTemp = _mm_shufflelo_epi16 (vTemp, 0);
  vTemp = _mm_shuffle_epi32 (vTemp, 0);
  vCeiling = _mm_cmpeq_epi16 (vTemp, vTemp);
  vCeiling = _mm_srli_epi16 (vCeiling, 1);
  vCeiling = _mm_subs_epi16 (vCeiling, vTemp);
  vCeiling = _mm_subs_epi16 (vCeiling, vGapOpen);

  vNull = _mm_cmpeq_epi16 (vTemp, vTemp);
  vNull = _mm_slli_epi16 (vNull, 15);
  vScaleAmt = _mm_xor_si128 (vNull, vNull);

  /* Zero out the storage vector */
  vTemp = _mm_adds_epi16 (vNull, vGapOpen);
  for (i = 0; i < iter; i++) {
    _mm_store_si128 (pvH + i, vTemp);
    _mm_store_si128 (pvE + i, vNull);
  }

  /* initialize F */
  vF = vNull;
  vFPrev = vNull;

  /* load and scale H for the next round */
  vTemp = _mm_srli_si128 (vGapOpen, 14);
  vH = _mm_load_si128 (pvH + iter - 1);
  vH = _mm_adds_epi16 (vH, vTemp);

  for (i = 0; i < dbLength; ++i) {
    /* fetch first data asap. */
    pvScore = (__m128i *) profile + dbSeq[i] * iter;

    vF = vNull;

    vH = _mm_max_epi16 (vH, vFPrev);
    for (j = 0; j < iter; j++) {
      /* correct H from the previous columns F */
      vHNext = _mm_load_si128 (pvH + j);
      vHNext = _mm_max_epi16 (vHNext, vFPrev);

      /* load and correct E value */
      vE = _mm_load_si128 (pvE + j);
      vTemp = _mm_subs_epi16 (vHNext, vGapOpen);
      vE = _mm_max_epi16 (vE, vTemp);
      _mm_store_si128 (pvE + j, vE);

      /* add score to vH */
      vH = _mm_adds_epi16 (vH, *pvScore++);

      /* get max from vH, vE and vF */
      vH = _mm_max_epi16 (vH, vE);
      vH = _mm_max_epi16 (vH, vF);
      _mm_store_si128 (pvH + j, vH);

      /* update vF value */
      vH = _mm_subs_epi16 (vH, vGapOpen);
      vF = _mm_max_epi16 (vF, vH);

      /* load the next h values */
      vH = vHNext;
    }

    /* check if we need to scale before the next round */
    vTemp = _mm_cmpgt_epi16 (vF, vCeiling);
    cmp  = _mm_movemask_epi8 (vTemp);

    /* broadcast F values */
    vF = _mm_xor_si128 (vF, vNull);

    vTemp  = _mm_slli_si128 (vF, 2);
    vTemp = _mm_subs_epu16 (vTemp, vScaleAmt);
    vF = max_epu16 (vF, vTemp);

    vTemp  = _mm_slli_si128 (vF, 4);
    vScaleTmp = _mm_slli_si128 (vScaleAmt, 2);
    vScaleTmp = _mm_adds_epu16 (vScaleTmp, vScaleAmt);
    vTemp = _mm_subs_epu16 (vTemp, vScaleTmp);
    vF = max_epu16 (vF, vTemp);

    vTemp = _mm_slli_si128 (vScaleTmp, 4);
    vScaleTmp = _mm_adds_epu16 (vScaleTmp, vTemp);
    vTemp  = _mm_slli_si128 (vF, 8);
    vTemp = _mm_subs_epu16 (vTemp, vScaleTmp);
    vF = max_epu16 (vF, vTemp);

    /* scale if necessary */
    if (cmp != 0x0000) {
      __m128i vScale1;
      __m128i vScale2;

      vScale = _mm_slli_si128 (vF, 2);
      vScale = _mm_subs_epu16 (vScale, vGapOpen);
      vScale = _mm_subs_epu16 (vScale, vScaleAmt);

      vTemp = _mm_slli_si128 (vScale, 2);
      vTemp = _mm_subs_epu16 (vScale, vTemp);
      vScaleAmt = _mm_adds_epu16 (vScaleAmt, vTemp);
      vTemp = _mm_slli_si128 (vScale, 2);
      vTemp = _mm_subs_epu16 (vTemp, vScale);
      vScaleAmt = _mm_subs_epu16 (vScaleAmt, vTemp);

      /* rescale the previous F */
      vF = _mm_subs_epu16 (vF, vScale);

      /* check if we can continue in signed 16-bits */
      vTemp = _mm_xor_si128 (vF, vNull);
      vTemp = _mm_cmpgt_epi16 (vTemp, vCeiling);
      cmp  = _mm_movemask_epi8 (vTemp);
      if (cmp != 0x0000) {
        return OVERFLOW_SCORE;
      }

      vTemp   = _mm_adds_epi16 (vCeiling, vCeiling);
      vScale1 = _mm_subs_epu16 (vScale, vTemp);
      vScale2 = _mm_subs_epu16 (vScale, vScale1);

      /* scale all the vectors */
      for (j = 0; j < iter; j++) {
        /* load H and E */
        vH = _mm_load_si128 (pvH + j);
        vE = _mm_load_si128 (pvE + j);

        /* get max from vH, vE and vF */
        vH = _mm_subs_epi16 (vH, vScale1);
        vH = _mm_subs_epi16 (vH, vScale2);
        vE = _mm_subs_epi16 (vE, vScale1);
        vE = _mm_subs_epi16 (vE, vScale2);

        /* save the H and E */
        _mm_store_si128 (pvH + j, vH);
        _mm_store_si128 (pvE + j, vE);
      }

      vScale = vScaleAmt;
      for (j = 0; j < position; ++j) {
        vScale = _mm_slli_si128 (vScale, 2);
      }

      /* calculate the final scaling amount */
      vTemp   = _mm_xor_si128 (vTemp, vTemp);
      vScale1 = _mm_unpacklo_epi16 (vScale, vTemp);
      vScale2 = _mm_unpackhi_epi16 (vScale, vTemp);
      vScale  = _mm_add_epi32 (vScale1, vScale2);
      vTemp = _mm_srli_si128 (vScale, 8);
      vScale = _mm_add_epi32 (vScale, vTemp);
      vTemp = _mm_srli_si128 (vScale, 4);
      vScale = _mm_add_epi32 (vScale, vTemp);
      scale = (int) (unsigned short) _mm_extract_epi16 (vScale, 0);
      temp  = (int) (unsigned short) _mm_extract_epi16 (vScale, 1);
      scale = scale + (temp << 16);
    }

    /* scale the F value for the next round */
    vFPrev = _mm_slli_si128 (vF, 2);
    vFPrev = _mm_subs_epu16 (vFPrev, vScaleAmt);
    vFPrev = _mm_xor_si128 (vFPrev, vNull);

    /* load and scale H for the next round */
    vH = _mm_load_si128 (pvH + iter - 1);
    vH = _mm_xor_si128 (vH, vNull);
    vH = _mm_slli_si128 (vH, 2);
    vH = _mm_subs_epu16 (vH, vScaleAmt);
    vH = _mm_insert_epi16 (vH, gapOpen, 0);
    vH = _mm_xor_si128 (vH, vNull);
  }

  vH = _mm_load_si128 (pvH + offset);
  vH = _mm_max_epi16 (vH, vFPrev);
  for (j = 0; j < position; ++j) {
    vH = _mm_slli_si128 (vH, 2);
  }
  score = (int) (signed short) _mm_extract_epi16 (vH, 7);
  score = score + SHORT_BIAS;

  /* return largest score */
  distance = (queryLength + dbLength) * gapExtend;
  score = score - (gapOpen * 2) - distance + scale;

  return score;
}