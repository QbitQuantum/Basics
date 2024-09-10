void OnDeletePool() {

   // Note: DestroyThreadpoolEnvironment() in winbase.h
   //       calls TpDestroyCallbackEnviron() in winnt.h 
   //       that does... nothing
   //       So, we need to destroy the thread pool ourself
   if (g_pThreadPool != NULL) {
      CloseThreadpool(g_pThreadPool);
   }

   // Clean up callback environment; maybe useful in next version
   // See previous comment
   DestroyThreadpoolEnvironment(&g_callbackEnvironment);
}