  int* Code39Reader::findAsteriskPattern(Ref<BitArray> row){
    int width = row->getSize();
    int rowOffset = 0;
    while (rowOffset < width) {
      if (row->get(rowOffset)) {
        break;
      }
      rowOffset++;
    }

    int counterPosition = 0;
    const int countersLen = 9;
    int counters[countersLen];
    for (int i = 0; i < countersLen; i++) {
      counters[i] = 0;
    }
    int patternStart = rowOffset;
    bool isWhite = false;
    int patternLength = countersLen;

    for (int i = rowOffset; i < width; i++) {
      bool pixel = row->get(i);
      if (pixel ^ isWhite) {
        counters[counterPosition]++;
      } else {
        if (counterPosition == patternLength - 1) {
          if (toNarrowWidePattern(counters, countersLen) == ASTERISK_ENCODING) {
            // Look for whitespace before start pattern, >= 50% of width of
            // start pattern.
            long double longPatternOffset =
              fmaxl(0, patternStart - (i - patternStart) / 2);
            if (row->isRange(longPatternOffset, patternStart, false)) {
              int* resultValue = new int[2];
              resultValue[0] = patternStart;
              resultValue[1] = i;
              return resultValue;
            }
          }
          patternStart += counters[0] + counters[1];
          for (int y = 2; y < patternLength; y++) {
            counters[y - 2] = counters[y];
          }
          counters[patternLength - 2] = 0;
          counters[patternLength - 1] = 0;
          counterPosition--;
        } else {
          counterPosition++;
        }
        counters[counterPosition] = 1;
        isWhite = !isWhite;
      }
    }
    throw ReaderException("");
  }