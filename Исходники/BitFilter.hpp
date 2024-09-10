      /*** simple union */
      TM_INLINE
      void unionwith(const BitFilter<BITS>& rhs)
      {
#ifdef STM_USE_SSE
          for (uint32_t i = 0; i < VEC_BLOCKS; ++i)
              vec_filter[i] = _mm_or_si128(vec_filter[i], rhs.vec_filter[i]);
#else
          for (uint32_t i = 0; i < WORD_BLOCKS; ++i)
              word_filter[i] |= rhs.word_filter[i];
#endif
      }