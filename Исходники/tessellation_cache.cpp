  void SharedLazyTessellationCache::waitForUsersLessEqual(ThreadWorkState *const t_state,
							  const unsigned int users)
   {
     while( !(t_state->counter <= users) )
       {
#if defined(__MIC__)
	 _mm_delay_32(128);
#else
	 _mm_pause();
	 _mm_pause();
	 _mm_pause();
	 _mm_pause();
#endif
       }
   }