		Ref<Result> Code128Reader::decodeRow(int rowNumber, Ref<BitArray> row) {
		  int* startPatternInfo = NULL;
		  try {
        startPatternInfo = findStartPattern(row);
        int startCode = startPatternInfo[2];
        int codeSet;
        switch (startCode) {
          case CODE_START_A:
            codeSet = CODE_CODE_A;
            break;
          case CODE_START_B:
            codeSet = CODE_CODE_B;
            break;
          case CODE_START_C:
            codeSet = CODE_CODE_C;
            break;
          default:
            throw ReaderException("");
        }

        bool done = false;
        bool isNextShifted = false;

        std::string tmpResultString;
        std::stringstream tmpResultSStr; // used if its Code 128C

        int lastStart = startPatternInfo[0];
        int nextStart = startPatternInfo[1];
        int counters[countersLength] = {0,0,0,0,0,0};

        int lastCode = 0;
        int code = 0;
        int checksumTotal = startCode;
        int multiplier = 0;
        bool lastCharacterWasPrintable = true;

        while (!done) {
          bool unshift = isNextShifted;
          isNextShifted = false;

          // Save off last code
          lastCode = code;

          // Decode another code from image
          try {
            code = decodeCode(row, counters, sizeof(counters)/sizeof(int), nextStart);
          } catch (ReaderException const& re) {
            throw re;
          }

          // Remember whether the last code was printable or not (excluding CODE_STOP)
          if (code != CODE_STOP) {
            lastCharacterWasPrintable = true;
          }

          // Add to checksum computation (if not CODE_STOP of course)
          if (code != CODE_STOP) {
            multiplier++;
            checksumTotal += multiplier * code;
          }

          // Advance to where the next code will to start
          lastStart = nextStart;
          int _countersLength = sizeof(counters) / sizeof(int);
          for (int i = 0; i < _countersLength; i++) {
            nextStart += counters[i];
          }

          // Take care of illegal start codes
          switch (code) {
            case CODE_START_A:
            case CODE_START_B:
            case CODE_START_C:
              throw ReaderException("");
          }

          switch (codeSet) {

            case CODE_CODE_A:
              if (code < 64) {
                tmpResultString.append(1, (char) (' ' + code));
              } else if (code < 96) {
                tmpResultString.append(1, (char) (code - 64));
              } else {
                // Don't let CODE_STOP, which always appears, affect whether whether we think the
                // last code was printable or not.
                if (code != CODE_STOP) {
                  lastCharacterWasPrintable = false;
                }
                switch (code) {
                  case CODE_FNC_1:
                  case CODE_FNC_2:
                  case CODE_FNC_3:
                  case CODE_FNC_4_A:
                    // do nothing?
                    break;
                  case CODE_SHIFT:
                    isNextShifted = true;
                    codeSet = CODE_CODE_B;
                    break;
                  case CODE_CODE_B:
                    codeSet = CODE_CODE_B;
                    break;
                  case CODE_CODE_C:
                    codeSet = CODE_CODE_C;
                    break;
                  case CODE_STOP:
                    done = true;
                    break;
                }
              }
              break;
            case CODE_CODE_B:
              if (code < 96) {
                tmpResultString.append(1, (char) (' ' + code));
              } else {
                if (code != CODE_STOP) {
                  lastCharacterWasPrintable = false;
                }
                switch (code) {
                  case CODE_FNC_1:
                  case CODE_FNC_2:
                  case CODE_FNC_3:
                  case CODE_FNC_4_B:
                    // do nothing?
                    break;
                  case CODE_SHIFT:
                    isNextShifted = true;
                    codeSet = CODE_CODE_C;
                    break;
                  case CODE_CODE_A:
                    codeSet = CODE_CODE_A;
                    break;
                  case CODE_CODE_C:
                    codeSet = CODE_CODE_C;
                    break;
                  case CODE_STOP:
                    done = true;
                    break;
                }
              }
              break;
            case CODE_CODE_C:
              tmpResultSStr.str(std::string());
              // the code read in this case is the number encoded directly
              if (code < 100) {
                if (code < 10) {
 					        tmpResultSStr << '0';
 				        }
                tmpResultSStr << code;
 				        tmpResultString.append(tmpResultSStr.str());
              } else {
                if (code != CODE_STOP) {
                  lastCharacterWasPrintable = false;
                }
                switch (code) {
                  case CODE_FNC_1:
                    // do nothing?
                    break;
                  case CODE_CODE_A:
                    codeSet = CODE_CODE_A;
                    break;
                  case CODE_CODE_B:
                    codeSet = CODE_CODE_B;
                    break;
                  case CODE_STOP:
                    done = true;
                    break;
                }
              }
              break;
          }

          // Unshift back to another code set if we were shifted
          if (unshift) {
            switch (codeSet) {
              case CODE_CODE_A:
                codeSet = CODE_CODE_C;
                break;
              case CODE_CODE_B:
                codeSet = CODE_CODE_A;
                break;
              case CODE_CODE_C:
                codeSet = CODE_CODE_B;
                break;
            }
          }

        }

        // Check for ample whitespace following pattern, but, to do this we first need to remember that
        // we fudged decoding CODE_STOP since it actually has 7 bars, not 6. There is a black bar left
        // to read off. Would be slightly better to properly read. Here we just skip it:
        int width = row->getSize();
        while (nextStart < width && row->get(nextStart)) {
          nextStart++;
        }
        long minResult = 0;
#ifndef NOFMAXL
        minResult = fminl(width, nextStart + (nextStart - lastStart)/ 2);
#else
        minResult = fmin(width, nextStart + (nextStart - lastStart)/ 2);
#endif
        if (!row->isRange(nextStart, minResult, false)) {
          throw ReaderException("");
        }

        // Pull out from sum the value of the penultimate check code
        checksumTotal -= multiplier * lastCode;
        // lastCode is the checksum then:
        if (checksumTotal % 103 != lastCode) {
          throw ReaderException("");
        }

        // Need to pull out the check digits from string
        int resultLength = tmpResultString.length();
        // Only bother if the result had at least one character, and if the checksum digit happened to
        // be a printable character. If it was just interpreted as a control code, nothing to remove.
        if (resultLength > 0 && lastCharacterWasPrintable) {
          if (codeSet == CODE_CODE_C) {
            tmpResultString.erase(resultLength - 2, resultLength);
          } else {
            tmpResultString.erase(resultLength - 1, resultLength);
          }
        }

        Ref<String> resultString(new String(tmpResultString));
        if (tmpResultString.length() == 0) {
          // Almost surely a false positive
          throw ReaderException("");
        }

        float left = (float) (startPatternInfo[1] + startPatternInfo[0]) / 2.0f;
        float right = (float) (nextStart + lastStart) / 2.0f;

        std::vector< Ref<ResultPoint> > resultPoints(2);
        Ref<OneDResultPoint> resultPoint1(new OneDResultPoint(left, (float) rowNumber));
        Ref<OneDResultPoint> resultPoint2(new OneDResultPoint(right, (float) rowNumber));
        resultPoints[0] = resultPoint1;
        resultPoints[1] = resultPoint2;

        delete [] startPatternInfo;
        ArrayRef<unsigned char> resultBytes(1);
        return Ref<Result>(new Result(resultString, resultBytes, resultPoints,
            BarcodeFormat_CODE_128));
			} catch (ReaderException const& re) {
			  delete [] startPatternInfo;
			  return Ref<Result>();
			}
		}