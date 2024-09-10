__stdcall
#endif
void (*__swift_thread_key_destructor)(void *);

static void
#if defined(_M_IX86)
__stdcall
#endif
destroyTLS_CCAdjustmentThunk(void *ptr) {
  _stdlib_destroyTLS(ptr);
}

static inline int
_stdlib_thread_key_create(__swift_thread_key_t * _Nonnull key,
                          __swift_thread_key_destructor _Nullable destructor) {
  *key = FlsAlloc(destroyTLS_CCAdjustmentThunk);
  return *key != FLS_OUT_OF_INDEXES;
}

#endif

#if SWIFT_TLS_HAS_RESERVED_PTHREAD_SPECIFIC

SWIFT_RUNTIME_STDLIB_INTERNAL
void *
_swift_stdlib_threadLocalStorageGet(void) {
  void *value = SWIFT_THREAD_GETSPECIFIC(SWIFT_STDLIB_TLS_KEY);
  if (value)
    return value;
  
  static swift::OnceToken_t token;