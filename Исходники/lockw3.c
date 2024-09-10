static void lockEnsureGlobalLock(void)
{
  static INIT_ONCE init_once = INIT_ONCE_STATIC_INIT;
  BOOL b = InitOnceExecuteOnce(&init_once, lockEnsureGlobalLockCallback,
                               UNUSED_POINTER, NULL);
  AVER(b);
}