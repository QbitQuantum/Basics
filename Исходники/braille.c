static int
brl_writeWindow (BrailleDisplay *brl, const wchar_t *text) {
  if (text) {
    if (wmemcmp(text, textCharacters, brailleCount) != 0) {
      const wchar_t *address = text;
      int count = brailleCount;

      writeString("Visual \"");

      while (count-- > 0) {
        wchar_t character = *address++;

        switch (character) {
          case WC_C('"'):
          case WC_C('\\'):
            writeCharacter(WC_C('\\'));
          default:
            writeCharacter(character);
            break;
        }
      }

      writeString("\"");
      writeLine();

      wmemcpy(textCharacters, text, brailleCount);
    }
  }

  if (cellsHaveChanged(brailleCells, brl->buffer, brailleCount, NULL, NULL, NULL)) {
    writeString("Braille \"");
    writeDots(brl->buffer, brailleCount);
    writeString("\"");
    writeLine();
  }

  return 1;
}