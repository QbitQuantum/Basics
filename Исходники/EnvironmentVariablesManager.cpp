bool EnvironmentVariablesManager::IsOSVariableSet(const char* name) {
#ifdef WINDOWS
  size_t sz = 0;
  assert(getenv_s(&sz, NULL, 0, name) == 0);
  return sz > 0;
#else
  const char* value = std::getenv(name);
  return value != NULL && *value != '\0';
#endif
}