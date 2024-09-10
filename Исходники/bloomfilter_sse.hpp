 bool test(const index_t & kmer) const
 {
     __m128 __attribute__ ((aligned (16))) zero = _mm_setzero_si128();
     const size_t BitsPerElement = sizeof(block_t) * 8;
     const Hash hashfunction = Hash();
     kmer_t hashvalue = kmer;
     for (int hcount = this->h; hcount > 0; hcount--)
     {
         hashvalue = hashfunction(hashvalue);
         // we expect the compiler to automatically turn this into a shift because it's a const power of two
         size_t offset = (hashvalue % this->m) / BitsPerElement;
         if (_mm_movemask_epi8(
             _mm_cmpeq_epi32(
             _mm_and_ps(bitarray[offset],masks[hashvalue & (BitsPerElement-1)]),zero)) != 0xFFFF) return false;
     }
     return true;
 }