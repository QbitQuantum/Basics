static void
updateCache (BrailleContractionData *bcd) {
  {
    unsigned int count = getInputCount(bcd);

    if (count > bcd->table->cache.input.size) {
      unsigned int newSize = count | 0X7F;
      wchar_t *newCharacters = malloc(ARRAY_SIZE(newCharacters, newSize));

      if (!newCharacters) {
        logMallocError();
        bcd->table->cache.input.count = 0;
        goto inputDone;
      }

      if (bcd->table->cache.input.characters) free(bcd->table->cache.input.characters);
      bcd->table->cache.input.characters = newCharacters;
      bcd->table->cache.input.size = newSize;
    }

    wmemcpy(bcd->table->cache.input.characters, bcd->input.begin, count);
    bcd->table->cache.input.count = count;
    bcd->table->cache.input.consumed = getInputConsumed(bcd);
  }
inputDone:

  {
    unsigned int count = getOutputConsumed(bcd);

    if (count > bcd->table->cache.output.size) {
      unsigned int newSize = count | 0X7F;
      unsigned char *newCells = malloc(ARRAY_SIZE(newCells, newSize));

      if (!newCells) {
        logMallocError();
        bcd->table->cache.output.count = 0;
        goto outputDone;
      }

      if (bcd->table->cache.output.cells) free(bcd->table->cache.output.cells);
      bcd->table->cache.output.cells = newCells;
      bcd->table->cache.output.size = newSize;
    }

    memcpy(bcd->table->cache.output.cells, bcd->output.begin, count);
    bcd->table->cache.output.count = count;
    bcd->table->cache.output.maximum = getOutputCount(bcd);
  }
outputDone:

  if (bcd->input.offsets) {
    unsigned int count = getInputCount(bcd);

    if (count > bcd->table->cache.offsets.size) {
      unsigned int newSize = count | 0X7F;
      int *newArray = malloc(ARRAY_SIZE(newArray, newSize));

      if (!newArray) {
        logMallocError();
        bcd->table->cache.offsets.count = 0;
        goto offsetsDone;
      }

      if (bcd->table->cache.offsets.array) free(bcd->table->cache.offsets.array);
      bcd->table->cache.offsets.array = newArray;
      bcd->table->cache.offsets.size = newSize;
    }

    memcpy(bcd->table->cache.offsets.array, bcd->input.offsets, ARRAY_SIZE(bcd->input.offsets, count));
    bcd->table->cache.offsets.count = count;
  } else {
    bcd->table->cache.offsets.count = 0;
  }
offsetsDone:

  bcd->table->cache.cursorOffset = makeCachedCursorOffset(bcd);
  bcd->table->cache.expandCurrentWord = prefs.expandCurrentWord;
  bcd->table->cache.capitalizationMode = prefs.capitalizationMode;
}