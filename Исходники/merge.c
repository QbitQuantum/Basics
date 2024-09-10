void merge() {
#if defined(SSE_MERGE) || defined(SSE_MERGE_UNROLL)
  __m128i isTrue = _mm_set1_epi16(0xFFFF);
#endif

  for (int i = 0; i < NUM_PAGES; ++i) {
    //merge in everything thats different between the ref and the latest committed page (that we haven't touched)
    
#ifdef PREFETCH
    for (int pages = 1; pages <= PREFETCH_PAGES; pages++) {
      for (int bpp = 0; bpp < PREFETCH_BYTES_PER_PAGE; bpp++) {
        __builtin_prefetch( &LATEST[i+pages][bpp], 0/*read*/, 3/*high temporal locality*/ );
        __builtin_prefetch( &REF[i+pages][bpp], 0/*read*/, 3/*high temporal locality*/ );
	// don't prefetch LOCAL since we generally don't need it
        //__builtin_prefetch( &LOCAL[i+pages][bpp], 1/*write*/, 3/*high temporal locality*/ );
      }
    }
#endif

#ifdef BYTE_MERGE
    const char* latest = LATEST[i];
    const char* ref = REF[i];
    char* local = LOCAL[i];
    for (int j = 0; j < PAGE_SIZE; ++j) {
      if ( unlikely(latest[j]!=ref[j] && local[j]==ref[j]) ){
        local[j] = latest[j];
      }
    }
#endif
#ifdef WORD_MERGE
    const uint64_t* latest = (const uint64_t*) LATEST[i];
    const uint64_t* ref = (const uint64_t*) REF[i];
    uint64_t* local = (uint64_t*) LOCAL[i];

    for (int j = 0; j < (PAGE_SIZE/sizeof(uint64_t)); ++j) {

      // check for diff at word granularity first
      if ( unlikely(latest[j]!=ref[j]) ) {
        if ( local[j] == ref[j] ) {
          local[j] = latest[j];

        } else {
          // have to do byte-wise comparison
          const char* latestChar = (const char*) latest[j];
          const char* refChar = (const char*) ref[j];
          char* localChar = (char*) local[j];
          for ( int k = 0; k < sizeof(uint64_t); k++ ) {
            if ( latestChar[k] != refChar[k] && localChar[k] == refChar[k] ) {
              localChar[k] = latestChar[k];
            }
          }
        }
      }

    }
#endif
#ifdef SSE_MERGE 
    const char* latestP = LATEST[i];
    const char* refP = REF[i];
    char* localP = LOCAL[i];

    for (int j = 0; j < PAGE_SIZE; j += sizeof(__m128i)) {
      __m128i latest = _mm_load_si128( (__m128i*) (latestP+j) );
      __m128i ref = _mm_load_si128( (__m128i*) (refP+j) );
      __m128i latEqRef = _mm_cmpeq_epi8(latest, ref); // if latest == ref, latref is all ones

      if ( unlikely(!_mm_testc_si128(latEqRef, isTrue)) ) {
        // some bytes differ
	__m128i local = _mm_load_si128( (__m128i*) (localP+j) );
        __m128i localEqRef = _mm_cmpeq_epi8(local, ref);
        if ( _mm_testc_si128(localEqRef, isTrue) ) {
          // local == ref
          _mm_stream_si128( (__m128i*) (localP+j), latest );
        } else {
          // (~latref) & localref, bytes where lat!=ref && local==ref
          __m128i latestMask = _mm_andnot_si128( latEqRef, localEqRef );
          // new = (latestMask & latest) | (~latestMask & local);
          __m128i latestBytes = _mm_and_si128(latestMask, latest);
          __m128i localBytes = _mm_andnot_si128(latestMask, local);
          latestBytes = _mm_or_si128(latestBytes, localBytes);
          _mm_stream_si128( (__m128i*) (localP+j), latestBytes );
        }
      }
    }
#endif
#ifdef SSE_MERGE_NOBRANCH
    for (int j = 0; j < PAGE_SIZE; j += sizeof(__m128i)) {
      __m128i latest = _mm_load_si128( (__m128i*) &LATEST[i][j] );
      __m128i ref = _mm_load_si128( (__m128i*) &REF[i][j] );
      __m128i local = _mm_load_si128( (__m128i*) &LOCAL[i][j] );
      __m128i latref = _mm_cmpeq_epi8(latest, ref); // if latest == ref, latref is all ones
      __m128i tmp = _mm_cmpeq_epi8(local, ref);
      latref = _mm_andnot_si128( latref, tmp ); // (~latref) & localref
      // update = (latref & latest) | (~latref & local);
      tmp = _mm_and_si128(latref, latest);
      __m128i localBytes = _mm_andnot_si128(latref, local);
      tmp = _mm_or_si128(tmp, localBytes);
      _mm_stream_si128( (__m128i*) &LOCAL[i][j], tmp );
    }
#endif
#ifdef SSE_MERGE_UNROLL
    // manually unroll this loop since gcc won't do it; ugh
    const char* latestP = LATEST[i];
    const char* refP = REF[i];
    char* localP = LOCAL[i];

    for (int j = 0; j < PAGE_SIZE; j += sizeof(__m128i)) {
      __m128i latest = _mm_load_si128( (__m128i*) (latestP+j) );
      __m128i ref = _mm_load_si128( (__m128i*) (refP+j) );
      __m128i latEqRef = _mm_cmpeq_epi8(latest, ref); // if latest == ref, latref is all ones

      if ( unlikely(!_mm_testc_si128(latEqRef, isTrue)) ) {
        // some bytes differ
	__m128i local = _mm_load_si128( (__m128i*) (localP+j) );
        __m128i localEqRef = _mm_cmpeq_epi8(local, ref);
        if ( _mm_testc_si128(localEqRef, isTrue) ) {
          // local == ref
          _mm_stream_si128( (__m128i*) (localP+j), latest );
        } else {
          // (~latref) & localref, bytes where lat!=ref && local==ref
          __m128i latestMask = _mm_andnot_si128( latEqRef, localEqRef );
          // new = (latestMask & latest) | (~latestMask & local);
          __m128i latestBytes = _mm_and_si128(latestMask, latest);
          __m128i localBytes = _mm_andnot_si128(latestMask, local);
          latestBytes = _mm_or_si128(latestBytes, localBytes);
          _mm_stream_si128( (__m128i*) (localP+j), latestBytes );
        }
      }

      j += sizeof(__m128i);
      latest = _mm_load_si128( (__m128i*) (latestP+j) );
      ref = _mm_load_si128( (__m128i*) (refP+j) );
      latEqRef = _mm_cmpeq_epi8(latest, ref); // if latest == ref, latref is all ones

      if ( unlikely(!_mm_testc_si128(latEqRef, isTrue)) ) {
        // some bytes differ
	__m128i local = _mm_load_si128( (__m128i*) (localP+j) );
        __m128i localEqRef = _mm_cmpeq_epi8(local, ref);
        if ( _mm_testc_si128(localEqRef, isTrue) ) {
          // local == ref
          _mm_stream_si128( (__m128i*) (localP+j), latest );
        } else {
          // (~latref) & localref, bytes where lat!=ref && local==ref
          __m128i latestMask = _mm_andnot_si128( latEqRef, localEqRef );
          // new = (latestMask & latest) | (~latestMask & local);
          __m128i latestBytes = _mm_and_si128(latestMask, latest);
          __m128i localBytes = _mm_andnot_si128(latestMask, local);
          latestBytes = _mm_or_si128(latestBytes, localBytes);
          _mm_stream_si128( (__m128i*) (localP+j), latestBytes );
        }
      }

      j += sizeof(__m128i);
      latest = _mm_load_si128( (__m128i*) (latestP+j) );
      ref = _mm_load_si128( (__m128i*) (refP+j) );
      latEqRef = _mm_cmpeq_epi8(latest, ref); // if latest == ref, latref is all ones

      if ( unlikely(!_mm_testc_si128(latEqRef, isTrue)) ) {
        // some bytes differ
	__m128i local = _mm_load_si128( (__m128i*) (localP+j) );
        __m128i localEqRef = _mm_cmpeq_epi8(local, ref);
        if ( _mm_testc_si128(localEqRef, isTrue) ) {
          // local == ref
          _mm_stream_si128( (__m128i*) (localP+j), latest );
        } else {
          // (~latref) & localref, bytes where lat!=ref && local==ref
          __m128i latestMask = _mm_andnot_si128( latEqRef, localEqRef );
          // new = (latestMask & latest) | (~latestMask & local);
          __m128i latestBytes = _mm_and_si128(latestMask, latest);
          __m128i localBytes = _mm_andnot_si128(latestMask, local);
          latestBytes = _mm_or_si128(latestBytes, localBytes);
          _mm_stream_si128( (__m128i*) (localP+j), latestBytes );
        }
      }

    }
#endif


  }
}