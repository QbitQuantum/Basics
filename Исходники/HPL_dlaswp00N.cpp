 inline void operator()(const tbb::blocked_range<size_t> &range) const {
     for (size_t colIndex = range.begin(); colIndex < range.end(); ++colIndex) {
         double *__restrict__ col = &A[colIndex * LDA];
         int i = 0;
         for (; i < permSize - 8; i += 2) {
             //_m_prefetchw(&col[p[8].a]);
             //_m_prefetchw(&col[p[8].b]);
             swap(col[perm[i + 0].a], col[perm[i + 0].b]);
             swap(col[perm[i + 1].a], col[perm[i + 1].b]);
         }
         for (; i < permSize; ++i) {
             const int rowIndex = perm[i].a;
             const int otherRow = perm[i].b;
             swap(col[rowIndex], col[otherRow]);
         }
     }
     _mm_mfence();
 }