void Impersonator::revertToSelf()
{
  if (m_dupToken != INVALID_HANDLE_VALUE) {
    CloseHandle(m_dupToken);
  }

  if (m_token != INVALID_HANDLE_VALUE) {
    CloseHandle(m_token);
  }

  m_dupToken = INVALID_HANDLE_VALUE;
  m_token = INVALID_HANDLE_VALUE;

  if (!RevertToSelf()) {
    throw SystemException();
  }
}