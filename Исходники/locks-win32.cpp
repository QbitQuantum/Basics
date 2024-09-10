void TRI_DestroyCondition(TRI_condition_t* cond) {
  DeleteCriticalSection(&cond->_lockWaiters);
}