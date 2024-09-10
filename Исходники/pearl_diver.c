DWORD WINAPI find_nonce(void* data) {
#else
void* find_nonce(void* data) {
#endif
  bc_trit_t midStateCopyLow[STATE_LENGTH], midStateCopyHigh[STATE_LENGTH];
  int i, shift;
  bc_trit_t nonce_probe, nonce_output;
  PDThread* my_thread = (PDThread*)data;
  char* trits = my_thread->trits;

  memset(midStateCopyLow, 0, STATE_LENGTH * sizeof(bc_trit_t));
  memset(midStateCopyHigh, 0, STATE_LENGTH * sizeof(bc_trit_t));
  PearlDiver* ctx = my_thread->ctx;
  memcpy(midStateCopyLow, my_thread->states->mid_low,
         STATE_LENGTH * sizeof(bc_trit_t));
  memcpy(midStateCopyHigh, my_thread->states->mid_high,
         STATE_LENGTH * sizeof(bc_trit_t));

  for (i = my_thread->threadIndex; i-- > 0;) {
    pd_increment(midStateCopyLow, midStateCopyHigh, NONCE_INIT_START,
        NONCE_INCREMENT_START);
  }

  bc_trit_t scratchpadLow[STATE_LENGTH], scratchpadHigh[STATE_LENGTH],
      stateLow[STATE_LENGTH], stateHigh[STATE_LENGTH];
  memset(stateLow, 0, STATE_LENGTH * sizeof(bc_trit_t));
  memset(stateHigh, 0, STATE_LENGTH * sizeof(bc_trit_t));
  memset(scratchpadLow, 0, STATE_LENGTH * sizeof(bc_trit_t));
  memset(scratchpadHigh, 0, STATE_LENGTH * sizeof(bc_trit_t));

  while (ctxStatusEq(my_thread, ctx, PD_SEARCHING)) {
    pd_increment(midStateCopyLow, midStateCopyHigh, NONCE_INCREMENT_START,
                 HASH_LENGTH);
    memcpy(stateLow, midStateCopyLow, STATE_LENGTH * sizeof(bc_trit_t));
    memcpy(stateHigh, midStateCopyHigh, STATE_LENGTH * sizeof(bc_trit_t));
    pd_transform(stateLow, stateHigh, scratchpadLow, scratchpadHigh);

    if ((nonce_probe = is_found_fast(stateLow, stateHigh,
                                     my_thread->min_weight_magnitude)) == 0)
      continue;

#if defined(_WIN32) && !defined(__MINGW32__)
#ifdef _WIN64
    _BitScanForward64(&shift, nonce_probe);
#else
    _BitScanForward(&shift, nonce_probe);
#endif
    nonce_output = 1 << shift;
    EnterCriticalSection(&my_thread->ctx->new_thread_search);
#else
    shift = __builtin_ctzll(nonce_probe);
    nonce_output = 1 << shift;
    pthread_mutex_lock(&my_thread->ctx->new_thread_search);
#endif

    if (ctx->status != PD_FOUND) {
      ctx->status = PD_FOUND;
      for (i = 0; i < HASH_LENGTH; i++) {
        trits[i] =
            (((bc_trit_t)(midStateCopyLow[i]) & nonce_output) == 0)
                ? 1
                : ((((bc_trit_t)(midStateCopyHigh[i]) & nonce_output) == 0) ? -1
                                                                         : 0);
      }
    }

#if defined(_WIN32) && !defined(__MINGW32__)
    LeaveCriticalSection(&my_thread->ctx->new_thread_search);
#else
    pthread_mutex_unlock(&my_thread->ctx->new_thread_search);
#endif

    return 0;
  }
  return 0;
}