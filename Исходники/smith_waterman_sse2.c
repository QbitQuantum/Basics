int
smith_waterman_sse2_byte(const unsigned char *     query_sequence,
                         unsigned char *     query_profile_byte,
                         const int                 query_length,
                         const unsigned char *     db_sequence,
                         const int                 db_length,
                         unsigned char       bias,
                         unsigned char       gap_open,
                         unsigned char       gap_extend,
                         struct f_struct *   f_str)
{
    int     i, j, k;
    int     score;

    int     dup;
    int     cmp;
    int     iter = (query_length + 15) / 16;
    
    __m128i *p;
    __m128i *workspace = (__m128i *) f_str->workspace;

    __m128i E, F, H;

    __m128i v_maxscore;
    __m128i v_bias;
    __m128i v_gapopen;
    __m128i v_gapextend;

    __m128i v_temp;
    __m128i v_zero;

    __m128i *pHLoad, *pHStore;
    __m128i *pE;

    __m128i *pScore;

    /* Load the bias to all elements of a constant */
    dup    = ((short) bias << 8) | bias;
    v_bias = _mm_setzero_si128();
    v_bias = _mm_insert_epi16 (v_bias, dup, 0);
    v_bias = _mm_shufflelo_epi16 (v_bias, 0);
    v_bias = _mm_shuffle_epi32 (v_bias, 0);

    /* Load gap opening penalty to all elements of a constant */
    dup  = ((short) gap_open << 8) | gap_open;
    v_gapopen = _mm_setzero_si128();
    v_gapopen = _mm_insert_epi16 (v_gapopen, dup, 0);
    v_gapopen = _mm_shufflelo_epi16 (v_gapopen, 0);
    v_gapopen = _mm_shuffle_epi32 (v_gapopen, 0);

    /* Load gap extension penalty to all elements of a constant */
    dup  = ((short) gap_extend << 8) | gap_extend;
    v_gapextend = _mm_setzero_si128();
    v_gapextend = _mm_insert_epi16 (v_gapextend, dup, 0);
    v_gapextend = _mm_shufflelo_epi16 (v_gapextend, 0);
    v_gapextend = _mm_shuffle_epi32 (v_gapextend, 0);

    /* initialize the max score */
    /*     v_maxscore = _mm_xor_si128 (v_maxscore, v_maxscore);  - Apple Devel*/
    v_maxscore = _mm_setzero_si128();	/* Apple Devel */

    /* create a constant of all zeros for comparison */
    /* v_zero = _mm_xor_si128 (v_zero, v_zero);   - Apple Devel */
    v_zero = _mm_setzero_si128();	/* Apple Devel */

    /* Zero out the storage vector */
    k = iter * 2;

    p = workspace;
    for (i = 0; i < k; i++)
    {
        _mm_store_si128 (p++, v_maxscore);
    }

    pE = workspace;
    pHStore = pE + iter;
    pHLoad = pHStore + iter;

    for (i = 0; i < db_length; ++i)
    {
        /* fetch first data asap. */
        pScore = (__m128i *) query_profile_byte + db_sequence[i] * iter;

        /* zero out F value. */
        /* F = _mm_xor_si128 (F, F);  -Apple Devel */
        F = _mm_setzero_si128();	/* Apple Devel */

        /* load the next h value */
        H = _mm_load_si128 (pHStore + iter - 1);
        H = _mm_slli_si128 (H, 1);

        p = pHLoad;
        pHLoad = pHStore;
        pHStore = p;

        for (j = 0; j < iter; j++)
        {
            /* load values E. */
            E = _mm_load_si128 (pE + j);

            /* add score to H */
            H = _mm_adds_epu8 (H, *pScore++);
            H = _mm_subs_epu8 (H, v_bias);

            /* Update highest score encountered this far */
            v_maxscore = _mm_max_epu8 (v_maxscore, H);

            /* get max from H, E and F */
            H = _mm_max_epu8 (H, E);
            H = _mm_max_epu8 (H, F);

            /* save H values */
            _mm_store_si128 (pHStore + j, H);

            /* subtract the gap open penalty from H */
            H = _mm_subs_epu8 (H, v_gapopen);

            /* update E value */
            E = _mm_subs_epu8 (E, v_gapextend);
            E = _mm_max_epu8 (E, H);

            /* update F value */
            F = _mm_subs_epu8 (F, v_gapextend);
            F = _mm_max_epu8 (F, H);

            /* save E values */
            _mm_store_si128 (pE + j, E);

            /* load the next h value */
            H = _mm_load_si128 (pHLoad + j);
        }

        /* reset pointers to the start of the saved data */
        j = 0;
        H = _mm_load_si128 (pHStore + j);

        /*  the computed F value is for the given column.  since */
        /*  we are at the end, we need to shift the F value over */
        /*  to the next column. */
        F = _mm_slli_si128 (F, 1);
        v_temp = _mm_subs_epu8 (H, v_gapopen);
        v_temp = _mm_subs_epu8 (F, v_temp);
        v_temp = _mm_cmpeq_epi8 (v_temp, v_zero);
        cmp  = _mm_movemask_epi8 (v_temp);

        while (cmp != 0xffff) 
        {
            E = _mm_load_si128 (pE + j);

            H = _mm_max_epu8 (H, F);

            /* save H values */
            _mm_store_si128 (pHStore + j, H);

            /* update E in case the new H value would change it */
            H = _mm_subs_epu8 (H, v_gapopen);
            E = _mm_max_epu8 (E, H);
            _mm_store_si128 (pE + j, E);

            /* update F value */
            F = _mm_subs_epu8 (F, v_gapextend);

            j++;
            if (j >= iter)
            {
                j = 0;
                F = _mm_slli_si128 (F, 1);
            }
            H = _mm_load_si128 (pHStore + j);

            v_temp = _mm_subs_epu8 (H, v_gapopen);
            v_temp = _mm_subs_epu8 (F, v_temp);
            v_temp = _mm_cmpeq_epi8 (v_temp, v_zero);
            cmp  = _mm_movemask_epi8 (v_temp);
        }
    }

    /* find largest score in the v_maxscore vector */
    v_temp = _mm_srli_si128 (v_maxscore, 8);
    v_maxscore = _mm_max_epu8 (v_maxscore, v_temp);
    v_temp = _mm_srli_si128 (v_maxscore, 4);
    v_maxscore = _mm_max_epu8 (v_maxscore, v_temp);
    v_temp = _mm_srli_si128 (v_maxscore, 2);
    v_maxscore = _mm_max_epu8 (v_maxscore, v_temp);
    v_temp = _mm_srli_si128 (v_maxscore, 1);
    v_maxscore = _mm_max_epu8 (v_maxscore, v_temp);

    /* store in temporary variable */
    score = _mm_extract_epi16 (v_maxscore, 0);
    score = score & 0x00ff;

    /*  check if we might have overflowed */
    if (score + bias >= 255)
    {
        score = 255;
    }

    /* return largest score */
    return score;
}