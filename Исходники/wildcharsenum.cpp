int WildcharsEnumerator::isWildchars(const char *filename) {
  return (STRCHR(filename, '*') || STRCHR(filename, '?'));
}