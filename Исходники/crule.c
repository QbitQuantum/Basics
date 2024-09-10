static void crule_getword(char* word, int* wordlenp, size_t maxlen, const char** ruleptr)
{
  char *word_ptr;

  word_ptr = word;
  while ((size_t)(word_ptr - word) < maxlen
      && (IsAlnum(**ruleptr)
      || **ruleptr == '*' || **ruleptr == '?'
      || **ruleptr == '.' || **ruleptr == '-'))
    *word_ptr++ = *(*ruleptr)++;
  *word_ptr = '\0';
  *wordlenp = word_ptr - word;
}