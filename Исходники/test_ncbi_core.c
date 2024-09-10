static void TEST_CORE_Log(void)
{
  /* LOG */
  LOG x_log;

  /* protective MT-lock */
  MT_LOCK x_lock;

  /* ELOG_Level, LOG_LevelStr() */
  int x_level;
  for (x_level = 0;  x_level <= (int) eLOG_Fatal;  x_level++) {
    switch ( (ELOG_Level) x_level ) {
    case eLOG_Trace:
    case eLOG_Note:
    case eLOG_Warning:
    case eLOG_Error:
    case eLOG_Critical:
    case eLOG_Fatal:
      assert(LOG_LevelStr((ELOG_Level) x_level));
      printf("LOG_LevelStr(level = %d): \"%s\"\n",
             x_level, LOG_LevelStr((ELOG_Level) x_level));
      break;
    default:
      assert(0);
    }
  }

  /* LOG API */

  /* MT-lock */
  x_lock = MT_LOCK_Create(&TEST_CORE_LockUserData,
                          TEST_CORE_LockHandler, TEST_CORE_LockCleanup);

  /* dummy */
  TEST_CORE_LogUserData = 1;
  x_log = LOG_Create(&TEST_CORE_LogUserData,
                     TEST_CORE_LogHandler, TEST_CORE_LogCleanup,
                     x_lock);
  assert(x_log);

  verify(LOG_AddRef(x_log) == x_log);
  verify(LOG_AddRef(x_log) == x_log);
  verify(LOG_Delete(x_log) == x_log);
  assert(TEST_CORE_LogUserData == 1);

  LOG_WRITE(0, 0, 0, eLOG_Trace, 0);
  LOG_Write(0, 0, 0, eLOG_Trace, 0, 0, 0, 0, 0, 0);
  LOG_WRITE(x_log, 0, 0, eLOG_Trace, 0);
  LOG_Write(x_log, 0, 0, eLOG_Trace, 0, 0, 0, 0, 0, 0);

  verify(LOG_Delete(x_log) == x_log);
  assert(TEST_CORE_LogUserData == 1);

  /* reset to "real" logging */
  LOG_Reset(x_log, &TEST_CORE_LogUserData,
            TEST_CORE_LogHandler, TEST_CORE_LogCleanup);
  assert(TEST_CORE_LogUserData == 444);
  TEST_CORE_LogUserData = 2;

  /* do the test logging */
  LOG_WRITE(x_log, 0, 0, eLOG_Trace, 0);
  LOG_Write(x_log, 0, 0, eLOG_Trace, 0, 0, 0, 0, 0, 0);
  LOG_WRITE(x_log, 0, 0, eLOG_Warning, "");
  /* LOG_WRITE(x_log, eLOG_Fatal, "Something fatal"); */
#undef  THIS_MODULE
#define THIS_MODULE "FooModuleName"
  LOG_WRITE(x_log, 0, 0, eLOG_Error, "With changed module name");
#undef  THIS_FILE
#define THIS_FILE "BarFileName"
  LOG_WRITE(x_log, 0, 0, eLOG_Critical, "With changed module and file name");
#undef  THIS_FILE
#define THIS_FILE __FILE__
#undef  THIS_MODULE
#define THIS_MODULE 0

  /* delete */
  verify(LOG_Delete(x_log) == 0);
  assert(TEST_CORE_LogUserData == 444);
}