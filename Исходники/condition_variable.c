int embb_condition_wait(embb_condition_t* condition_var,
                        embb_mutex_t* mutex) {
  assert(condition_var != NULL);
  assert(mutex != NULL);
  if (SleepConditionVariableCS(condition_var, mutex, INFINITE)) {
    return EMBB_SUCCESS;
  }
  return EMBB_ERROR;
}