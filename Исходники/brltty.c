size_t
formatCharacterDescription (char *buffer, size_t size, int column, int row) {
  static char *const colours[] = {
    strtext("black"),
    strtext("blue"),
    strtext("green"),
    strtext("cyan"),
    strtext("red"),
    strtext("magenta"),
    strtext("brown"),
    strtext("light grey"),
    strtext("dark grey"),
    strtext("light blue"),
    strtext("light green"),
    strtext("light cyan"),
    strtext("light red"),
    strtext("light magenta"),
    strtext("yellow"),
    strtext("white")
  };

  size_t length;
  ScreenCharacter character;

  readScreen(column, row, 1, 1, &character);
  STR_BEGIN(buffer, size);

  {
    uint32_t text = character.text;

    STR_PRINTF("char %" PRIu32 " (U+%04" PRIX32 "): %s on %s",
               text, text,
               gettext(colours[character.attributes & 0X0F]),
               gettext(colours[(character.attributes & 0X70) >> 4]));
  }

  if (character.attributes & SCR_ATTR_BLINK) {
    STR_PRINTF(" %s", gettext("blink"));
  }

#ifdef HAVE_ICU
  {
    char name[0X40];
    UErrorCode error = U_ZERO_ERROR;

    u_charName(character.text, U_EXTENDED_CHAR_NAME, name, sizeof(name), &error);
    if (U_SUCCESS(error)) {
      STR_PRINTF(" [%s]", name);
    }
  }
#endif /* HAVE_ICU */

  length = STR_LENGTH;
  STR_END;
  return length;
}