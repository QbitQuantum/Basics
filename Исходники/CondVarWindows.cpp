void	CondVarWindows::broadcast()
{
  WakeAllConditionVariable(&this->_condvar);
}