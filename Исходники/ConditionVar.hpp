 inline void CondBroadcast(ConditionVariable* var)
 {
   WakeAllConditionVariable(&var->m_Impl);
 }