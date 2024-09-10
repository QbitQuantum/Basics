bool processWorkingSetSigaction(int SigNum, const void *ActVoid,
                                void *OldActVoid) {
  VPrintf(2, "%s: %d\n", __FUNCTION__, SigNum);
  if (SigNum == SIGSEGV) {
    const struct sigaction *Act = (const struct sigaction *) ActVoid;
    struct sigaction *OldAct = (struct sigaction *) OldActVoid;
    if (OldAct)
      internal_memcpy(OldAct, &AppSigAct, sizeof(OldAct));
    if (Act)
      internal_memcpy(&AppSigAct, Act, sizeof(AppSigAct));
    return false; // Skip real call.
  }
  return true;
}