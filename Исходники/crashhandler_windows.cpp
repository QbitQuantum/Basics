   void installCrashHandler() {
      internal::installSignalHandler();
      g_previous_unexpected_exception_handler = SetUnhandledExceptionFilter(unexpectedExceptionHandling);

#if !(defined(DISABLE_VECTORED_EXCEPTIONHANDLING))
      // const size_t kFirstExceptionHandler = 1;
      // kFirstExeptionsHandler is kept here for documentation purposes.
      // The last exception seems more like what we want.
      const size_t kLastExceptionHandler = 0;
      g_vector_exception_handler = AddVectoredExceptionHandler(kLastExceptionHandler, vectorExceptionHandling);
#endif
   }