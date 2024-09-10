int gpr_cv_wait(gpr_cv *cv, gpr_mu *mu, gpr_timespec abs_deadline) {
  int timeout = 0;
  DWORD timeout_max_ms;
  mu->locked = 0;
  if (gpr_time_cmp(abs_deadline, gpr_inf_future) == 0) {
    SleepConditionVariableCS(cv, &mu->cs, INFINITE);
  } else {
    gpr_timespec now = gpr_now();
    gpr_int64 now_ms = now.tv_sec * 1000 + now.tv_nsec / 1000000;
    gpr_int64 deadline_ms =
        abs_deadline.tv_sec * 1000 + abs_deadline.tv_nsec / 1000000;
    if (now_ms >= deadline_ms) {
      timeout = 1;
    } else {
      timeout_max_ms = (DWORD)min(deadline_ms - now_ms, INFINITE - 1);
      timeout = (SleepConditionVariableCS(cv, &mu->cs, timeout_max_ms) == 0 &&
                 GetLastError() == ERROR_TIMEOUT);
    }
  }
  mu->locked = 1;
  return timeout;
}