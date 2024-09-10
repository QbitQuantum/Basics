void AttemptToDeleteTestFile(char const *path) {
  DWORD attr;

  attr = GetFileAttributesA(path);
  CHECK(INVALID_FILE_ATTRIBUTES != attr);
  if (0 != (attr & FILE_ATTRIBUTE_READONLY)) {
    attr &= ~FILE_ATTRIBUTE_READONLY;
    CHECK(SetFileAttributesA(path, attr));
  }
  if (!DeleteFileA(path)) {
    DWORD err = GetLastError();
    NaClLog(LOG_WARNING, "DeleteFileA failed, error %d\n", err);
  }
}