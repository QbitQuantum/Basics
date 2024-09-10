// __asm__ blocks are only checked for inline functions that end up being
// emitted, so call functions with __asm__ blocks to make sure their inline
// assembly parses.
void f() {
  __movsb(0, 0, 0);
  __movsd(0, 0, 0);
  __movsw(0, 0, 0);

  __stosd(0, 0, 0);
  __stosw(0, 0, 0);

#ifdef _M_X64
  __movsq(0, 0, 0);
  __stosq(0, 0, 0);
#endif

  int info[4];
  __cpuid(info, 0);
  __cpuidex(info, 0, 0);
  _xgetbv(0);
  __halt();
  __nop();
  __readmsr(0);

  // FIXME: Call these in 64-bit too once the intrinsics have been fixed to
  // work there, PR19301
#ifndef _M_X64
  __readcr3();
  __writecr3(0);
#endif

#ifdef _M_ARM
  __dmb(_ARM_BARRIER_ISHST);
#endif
}