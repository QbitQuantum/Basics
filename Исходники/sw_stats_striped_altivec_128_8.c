static inline void arr_store_col(
        int *col,
        vec128i vH,
        int32_t t,
        int32_t seglen,
        int32_t bias)
{
    col[ 0*seglen+t] = (int8_t)_mm_extract_epi8(vH,  0) - bias;
    col[ 1*seglen+t] = (int8_t)_mm_extract_epi8(vH,  1) - bias;
    col[ 2*seglen+t] = (int8_t)_mm_extract_epi8(vH,  2) - bias;
    col[ 3*seglen+t] = (int8_t)_mm_extract_epi8(vH,  3) - bias;
    col[ 4*seglen+t] = (int8_t)_mm_extract_epi8(vH,  4) - bias;
    col[ 5*seglen+t] = (int8_t)_mm_extract_epi8(vH,  5) - bias;
    col[ 6*seglen+t] = (int8_t)_mm_extract_epi8(vH,  6) - bias;
    col[ 7*seglen+t] = (int8_t)_mm_extract_epi8(vH,  7) - bias;
    col[ 8*seglen+t] = (int8_t)_mm_extract_epi8(vH,  8) - bias;
    col[ 9*seglen+t] = (int8_t)_mm_extract_epi8(vH,  9) - bias;
    col[10*seglen+t] = (int8_t)_mm_extract_epi8(vH, 10) - bias;
    col[11*seglen+t] = (int8_t)_mm_extract_epi8(vH, 11) - bias;
    col[12*seglen+t] = (int8_t)_mm_extract_epi8(vH, 12) - bias;
    col[13*seglen+t] = (int8_t)_mm_extract_epi8(vH, 13) - bias;
    col[14*seglen+t] = (int8_t)_mm_extract_epi8(vH, 14) - bias;
    col[15*seglen+t] = (int8_t)_mm_extract_epi8(vH, 15) - bias;
}