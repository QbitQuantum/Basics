static int
processLine (char *line, void *data) {
  const char *string = line;
  size_t length = strlen(string);
  const char *byte = string;

  size_t count = length + 1;
  wchar_t characters[count];
  wchar_t *character = characters;

  convertUtf8ToWchars(&byte, &character, count);
  length = character - characters;
  character = characters;

  while (1) {
    const wchar_t *end = wmemchr(character, FF, length);
    if (!end) break;

    count = end - character;
    if (!processCharacters(character, count, *end, data)) return 0;

    count += 1;
    character += count;
    length -= count;
  }
  if (!processCharacters(character, length, '\n', data)) return 0;

  if (opt_forceOutput)
    if (!flushOutputStream(data))
      return 0;

  return 1;
}