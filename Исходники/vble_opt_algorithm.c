    VECTOR ri;
    VECTOR ro;
    VECTOR iBoxMinX;
    VECTOR iBoxMinY;
    VECTOR iBoxMaxX;
    VECTOR iBoxMaxY;
} anchor_info_t;

static inline void __attribute__((__always_inline__,__gnu_inline__,__nonnull__,__artificial__))
multilaterate(anchor_info_t *anchors, size_t num_anchors,
              VECTOR L, VECTOR last_L, VECTOR minX, VECTOR maxX,
              VECTOR minY, VECTOR maxY, VECTOR *restrict resx, VECTOR *restrict resy)
{
    // do iterative/recursive solution
    ivector_u maxScore;
    ivector_u maxScoreIndex = { _mm_set1_epi32(1) };
    VECTOR finalX = zero;
    VECTOR finalY = zero;

    VECTOR iterMinX = minX;
    VECTOR iterMaxX = maxX;
    VECTOR iterMinY = minY;
    VECTOR iterMaxY = maxY;
    
    // Note: The vectorized implementation can result in more iterations for some
    // values.
    while (! VECTOR_TEST_ALL_ONES(VECTOR_LT(L, last_L))) {
        finalX = zero;
        finalY = zero;
        maxScore.v = _mm_set1_epi32(0);
        maxScoreIndex.v = _mm_set1_epi32(0);