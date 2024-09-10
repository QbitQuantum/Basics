  RTCORE_API void rtcCommitThread(RTCScene hscene, unsigned int threadID, unsigned int numThreads) 
  {
    Scene* scene = (Scene*) hscene;
    RTCORE_CATCH_BEGIN;
    RTCORE_TRACE(rtcCommitThread);
    RTCORE_VERIFY_HANDLE(hscene);

    if (unlikely(numThreads == 0)) 
      throw_RTCError(RTC_INVALID_OPERATION,"invalid number of threads specified");

#if defined(__MIC__)
    if (unlikely(numThreads % 4 != 0 && numThreads != 1)) 
      throw_RTCError(RTC_INVALID_OPERATION,"MIC requires numThreads % 4 == 0 in rtcCommitThread");
#endif
    
    /* for best performance set FTZ and DAZ flags in the MXCSR control and status register */
#if !defined(__MIC__)
    unsigned int mxcsr = _mm_getcsr();
    _mm_setcsr(mxcsr | /* FTZ */ (1<<15) | /* DAZ */ (1<<6));
#endif
    
     /* perform scene build */
    scene->build(threadID,numThreads);

 /* reset MXCSR register again */
#if !defined(__MIC__)
    _mm_setcsr(mxcsr);
#endif

    RTCORE_CATCH_END(scene->device);
  }