bool fixMmapAddr(void **Addr, SIZE_T Size, int Flags) {
  if (*Addr) {
    if (!liesWithinSingleAppRegion((uptr)*Addr, Size)) {
      VPrintf(1, "mmap conflict: [%p-%p) is not in an app region\n",
              *Addr, (uptr)*Addr + Size);
      if (Flags & MAP_FIXED) {
        errno = EINVAL;
        return false;
      } else {
        *Addr = 0;
      }
    }
  }
  return true;
}