static inline void
init_static_vec2 (void)
{
  BOOL bStatus = InitOnceExecuteOnce (&static_vec2_once,
                                      InitVec2Func,
                                      NULL,
                                      NULL);
  if (!bStatus)
    fprintf (stderr, "InitOnceExecuteOnce failed\n");
}