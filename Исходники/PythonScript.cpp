bool PythonScript::executeImpl() {
  TemporaryValue holder(m_threadID, getThreadID());
  return executeString();
}