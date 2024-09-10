char *gpr_getenv(const char *name) {
  size_t size;
  char *result = NULL;
  errno_t err;

  err = getenv_s(&size, NULL, 0, name);
  if (err || (size == 0)) return NULL;
  result = gpr_malloc(size);
  err = getenv_s(&size, result, size, name);
  if (err) {
    gpr_free(result);
    return NULL;
  }
  return result;
}