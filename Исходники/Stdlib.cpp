int setenv(const char* name, const char* value, int overwrite) {
  if (overwrite == 0 && getenv(name) != nullptr) {
    return 0;
  }

  if (*value != '\0') {
    auto e = _putenv_s(name, value);
    if (e != 0) {
      errno = e;
      return -1;
    }
    return 0;
  }

  // We are trying to set the value to an empty string, but
  // _putenv_s deletes entries if the value is an empty string,
  // and just calling SetEnvironmentVariableA doesn't update
  // _environ, so we have to do these terrible things.
  if (_putenv_s(name, "  ") != 0) {
    errno = EINVAL;
    return -1;
  }

  // Here lies the documentation we blatently ignore to make
  // this work >_>...
  *getenv(name) = '\0';
  // This would result in a double null termination, which
  // normally signifies the end of the environment variable
  // list, so we stick a completely empty environment variable
  // into the list instead.
  *(getenv(name) + 1) = '=';

  // If _wenviron is null, the wide environment has not been initialized
  // yet, and we don't need to try to update it.
  // We have to do this otherwise we'd be forcing the initialization and
  // maintenance of the wide environment even though it's never actually
  // used in most programs.
  if (_wenviron != nullptr) {
    wchar_t buf[_MAX_ENV + 1];
    size_t len;
    if (mbstowcs_s(&len, buf, _MAX_ENV + 1, name, _MAX_ENV) != 0) {
      errno = EINVAL;
      return -1;
    }
    *_wgetenv(buf) = u'\0';
    *(_wgetenv(buf) + 1) = u'=';
  }

  // And now, we have to update the outer environment to have
  // a proper empty value.
  if (!SetEnvironmentVariableA(name, value)) {
    errno = EINVAL;
    return -1;
  }
  return 0;
}