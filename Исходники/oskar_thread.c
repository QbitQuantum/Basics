static void oskar_condition_wait(oskar_ConditionVar* var)
{
#if defined(OSKAR_OS_WIN)
    SleepConditionVariableCS(&var->var, &(var->lock.lock), INFINITE);
#else
    pthread_cond_wait(&var->var, &(var->lock.lock));
#endif
}