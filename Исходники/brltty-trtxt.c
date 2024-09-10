static int
processStream (FILE *inputStream, const char *inputName) {
  mbstate_t inputState;
  mbstate_t outputState;

  memset(&inputState, 0, sizeof(inputState));
  memset(&outputState, 0, sizeof(outputState));

  while (!feof(inputStream)) {
    char inputBuffer[0X1000];
    size_t inputCount = fread(inputBuffer, 1, sizeof(inputBuffer), inputStream);

    if (ferror(inputStream)) goto inputError;
    if (!inputCount) break;

    {
      char *byte = inputBuffer;

      while (inputCount) {
        wchar_t character;

        {
          size_t result = mbrtowc(&character, byte, inputCount, &inputState);

          if (result == (size_t)-2) break;
          if (result == (size_t)-1) goto inputError;
          if (!result) result = 1;

          byte += result;
          inputCount -= result;
        }

        if (!iswcntrl(character)) {
          unsigned char dots = toDots(character);

          if (dots || !iswspace(character)) {
            if (opt_sixDots) dots &= ~(BRL_DOT_7 | BRL_DOT_8);
            character = toCharacter(dots);
          }
        }

        if (!writeCharacter(&character, &outputState)) goto outputError;
      }
    }
  }

  if (!writeCharacter(NULL, &outputState)) goto outputError;
  fflush(outputStream);
  if (ferror(outputStream)) goto outputError;

  if (!mbsinit(&inputState)) {
#ifdef EILSEQ
    errno = EILSEQ;
#else /* EILSEQ */
    errno = EINVAL;
#endif /* EILSEQ */
    goto inputError;
  }

  return 1;

inputError:
  logMessage(LOG_ERR, "input error: %s: %s", inputName, strerror(errno));
  return 0;

outputError:
  logMessage(LOG_ERR, "output error: %s: %s", outputName, strerror(errno));
  return 0;
}