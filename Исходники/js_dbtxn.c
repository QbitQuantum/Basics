void compareSwapTs(Timestamp *dest, Timestamp *src, int chk) {
Timestamp cmp[1];

  do {
	cmp->epoch = dest->epoch;
	cmp->lowBits = dest->lowBits;

	if (chk > 0 && compareTs(cmp, src) <= 0)
	  return;

	if (chk < 0 && compareTs(cmp, src) >= 0)
	  return;

#ifdef _WIN32
  } while (!_InterlockedCompareExchange128((uint64_t *)dest, src->epoch, src->lowBits, (uint64_t *)cmp) );
#else
  } while (!__atomic_compare_exchange((__int128 *)dest, (__int128 *)cmp, (__int128 *)src, false, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE));