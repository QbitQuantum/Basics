inline char * getenv(char const* key) {
  //TODO: thread-safe version of getenv
  return GetEnvironmentVariableA(key, getenv_buf, getenv_maxch) ? getenv_buf : NULL;
}