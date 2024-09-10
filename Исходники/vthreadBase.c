static VThreadBaseKeyType
VThreadBaseGetKey(void)
{
   VThreadBaseKeyType key = Atomic_Read(&vthreadBaseGlobals.key);

   if (key == VTHREADBASE_INVALID_KEY) {
      VThreadBaseKeyType newKey;

#if defined _WIN32
      newKey = TlsAlloc();
      ASSERT_NOT_IMPLEMENTED(newKey != VTHREADBASE_INVALID_KEY);
#else
      Bool success = pthread_key_create(&newKey, 
                                        &VThreadBaseSafeDeleteTLS) == 0;
      if (success && newKey == 0) {
         /* 
          * Leak TLS key 0.  System libraries have a habit of destroying
          * it.  See bugs 702818 and 773420.
          */

         success = pthread_key_create(&newKey, 
                                      &VThreadBaseSafeDeleteTLS) == 0;
      }
      ASSERT_NOT_IMPLEMENTED(success);
#endif

      if (Atomic_ReadIfEqualWrite(&vthreadBaseGlobals.key,
                                  VTHREADBASE_INVALID_KEY,
                                  newKey) != VTHREADBASE_INVALID_KEY) {
         /* Race: someone else init'd */
#if defined _WIN32
         TlsFree(newKey);
#else
         pthread_key_delete(newKey);
#endif
      }

      key = Atomic_Read(&vthreadBaseGlobals.key);
      ASSERT(key != VTHREADBASE_INVALID_KEY);
   }

   return key;
}