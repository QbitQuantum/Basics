void PipeImpersonatedThread::execute()
{
  m_success = ImpersonateNamedPipeClient(m_pipeHandle) != 0;
  if (!m_success) {
    // Store fault reason
    Environment::getErrStr(&m_faultReason);
  }
  m_impersonationReadyEvent.notify();

  while (!isTerminating()) {
    m_threadSleeper.waitForEvent();
  }
  RevertToSelf();
}