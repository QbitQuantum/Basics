inline void
ConditionBroadcast (Condition* condition)
{
    WakeAllConditionVariable(condition);
}