    // ymm00 = _mm256_add_pd(ymm00, ymm01); ymm02 = _mm256_add_pd(ymm02, ymm03);
    // ymm04 = _mm256_add_pd(ymm04, ymm05); ymm06 = _mm256_add_pd(ymm06, ymm07);
    // ymm00 = _mm256_add_pd(ymm00, ymm02); ymm04 = _mm256_add_pd(ymm04, ymm06);
    // ymm00 = _mm256_add_pd(ymm00, ymm04);// ymm00 now holds the left half
    // // add up right half
    // ymm08 = _mm256_add_pd(ymm08, ymm09); ymm10 = _mm256_add_pd(ymm10, ymm11);
    // ymm12 = _mm256_add_pd(ymm12, ymm13); ymm14 = _mm256_add_pd(ymm14, ymm15);
    // ymm08 = _mm256_add_pd(ymm08, ymm10); ymm12 = _mm256_add_pd(ymm12, ymm14);
    // ymm08 = _mm256_add_pd(ymm08, ymm12);// ymm08 holds right half

    // // ym00 and ym08 now hold the left and right halves, store back in C
    // _mm256_store_pd((double *) (C + row*8), ymm00); _mm256_store_pd((double *) (C + row*8 + 4), ymm08);

    // Broadcast each element of matrix A Row [row] into a ymm register
    // If row = [ a b c d e f g h ], then we need two registers for each
    ymm00 = _mm256_broadcast_sd((double *)(A + row*8 + 0)); ymm01 = _mm256_broadcast_sd((double *)(A + row*8 + 0));// a
    ymm02 = _mm256_broadcast_sd((double *)(A + row*8 + 1)); ymm03 = _mm256_broadcast_sd((double *)(A + row*8 + 1));// b
    ymm04 = _mm256_broadcast_sd((double *)(A + row*8 + 2)); ymm05 = _mm256_broadcast_sd((double *)(A + row*8 + 2));// c
    ymm06 = _mm256_broadcast_sd((double *)(A + row*8 + 3)); ymm07 = _mm256_broadcast_sd((double *)(A + row*8 + 3));// d
    ymm08 = _mm256_broadcast_sd((double *)(A + row*8 + 4)); ymm09 = _mm256_broadcast_sd((double *)(A + row*8 + 4));// e
    ymm10 = _mm256_broadcast_sd((double *)(A + row*8 + 5)); ymm11 = _mm256_broadcast_sd((double *)(A + row*8 + 5));// f
    ymm12 = _mm256_broadcast_sd((double *)(A + row*8 + 6)); ymm13 = _mm256_broadcast_sd((double *)(A + row*8 + 6));// g
    ymm14 = _mm256_broadcast_sd((double *)(A + row*8 + 7)); ymm15 = _mm256_broadcast_sd((double *)(A + row*8 + 7));// h

    // multiply
    // left half
    ymm00 = _mm256_mul_pd(ymm00, ymm16); ymm01 = _mm256_mul_pd(ymm01, ymm17);// row 1
    ymm02 = _mm256_mul_pd(ymm02, ymm18); ymm03 = _mm256_mul_pd(ymm03, ymm19);// row 2
    ymm04 = _mm256_mul_pd(ymm04, ymm20); ymm05 = _mm256_mul_pd(ymm05, ymm21);// row 3
    ymm06 = _mm256_mul_pd(ymm06, ymm22); ymm07 = _mm256_mul_pd(ymm07, ymm23);// row 4
    ymm08 = _mm256_mul_pd(ymm08, ymm24); ymm09 = _mm256_mul_pd(ymm09, ymm25);// row 5