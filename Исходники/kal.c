void _debug_rstr_context(CONTEXT* __context__,kernel_pthread_t *__pthread_ptr__){
   CONTEXT __local_context__;
   __context__->ContextFlags=PTHREAD_CONTEXT_DUMP;
   memcpy(&__local_context__,__context__,sizeof(CONTEXT));
   SetThreadContext(__pthread_ptr__->tcb->hTask, &__local_context__);
}