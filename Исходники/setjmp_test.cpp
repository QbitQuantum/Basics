TEST(setjmp, _setjmp_signal_mask) {
  // _setjmp/_longjmp do not save/restore the signal mask.
  SigSets ss;
  sigprocmask(SIG_SETMASK, &ss.one, &ss.original);
  jmp_buf jb;
  if (_setjmp(jb) == 0) {
    sigprocmask(SIG_SETMASK, &ss.two, NULL);
    _longjmp(jb, 1);
    FAIL(); // Unreachable.
  } else {
    AssertSigmaskEquals(ss.two);
  }
  sigprocmask(SIG_SETMASK, &ss.original, NULL);
}