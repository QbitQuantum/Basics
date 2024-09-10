/*  From crlibm */
unsigned long long mwFixFPUPrecision(void)
{
#if MW_IS_X86_32

  #if defined(_MSC_VER) || defined(__MINGW32__)
  unsigned int oldcw, cw;

  /* CHECKME */
  oldcw = _controlfp(0, 0);

  #ifdef __MINGW32__
  _controlfp(_PC_53, _MCW_PC);
  #else
  _controlfp(_PC_53, MCW_PC);
  #endif

  return (unsigned long long) oldcw;

  #elif defined(__SUNPRO_C)  /* Sun Studio  */
  unsigned short oldcw, cw;

  __asm__ ("movw    $639, -22(%ebp)");
  __asm__ ("fldcw -22(%ebp)");

  return (unsigned long long) oldcw;
  #elif !defined(__APPLE__) /* GCC, clang */
  /* x87 FPU never used on OS X */
  unsigned short oldcw, cw;

    /* save old state */
  _FPU_GETCW(oldcw);
  /* Set FPU flags to use double, not double extended,
     with rounding to nearest */
  cw = (_FPU_DEFAULT & ~_FPU_EXTENDED)|_FPU_DOUBLE;
  _FPU_SETCW(cw);
  return (unsigned long long) oldcw;
  #else
  return 0;
  #endif /* defined(_MSC_VER) || defined(__MINGW32__) */
#else /* */
  return 0;
#endif /* MW_IS_X86 */
}