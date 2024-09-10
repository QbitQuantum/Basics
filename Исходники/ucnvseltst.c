static void TestSelector()
{
  TestText text;
  USet* excluded_sets[3] = { NULL };
  int32_t i, testCaseIdx;

  if (!getAvailableNames()) {
    return;
  }
  if (!text_open(&text)) {
    releaseAvailableNames();;
  }

  excluded_sets[0] = uset_openEmpty();
  for(i = 1 ; i < 3 ; i++) {
    excluded_sets[i] = uset_open(i*30, i*30+500);
  }

  for(testCaseIdx = 0; testCaseIdx < UPRV_LENGTHOF(getEncodingsFns); testCaseIdx++)
  {
    int32_t excluded_set_id;
    int32_t num_encodings;
    const char **encodings = getEncodingsFns[testCaseIdx](&num_encodings);
    if (getTestOption(QUICK_OPTION) && num_encodings > 25) {
      uprv_free((void *)encodings);
      continue;
    }

    /*
     * for(excluded_set_id = 0 ; excluded_set_id < 3 ; excluded_set_id++)
     *
     * This loop was replaced by the following statement because
     * the loop made the test run longer without adding to the code coverage.
     * The handling of the exclusion set is independent of the
     * set of encodings, so there is no need to test every combination.
     */
    excluded_set_id = testCaseIdx % UPRV_LENGTHOF(excluded_sets);
    {
      UConverterSelector *sel_rt, *sel_fb;
      char *buffer_fb = NULL;
      UErrorCode status = U_ZERO_ERROR;
      sel_rt = ucnvsel_open(encodings, num_encodings,
                            excluded_sets[excluded_set_id],
                            UCNV_ROUNDTRIP_SET, &status);
      if (num_encodings == gCountAvailable) {
        /* test the special "all converters" parameter values */
        sel_fb = ucnvsel_open(NULL, 0,
                              excluded_sets[excluded_set_id],
                              UCNV_ROUNDTRIP_AND_FALLBACK_SET, &status);
      } else if (uset_isEmpty(excluded_sets[excluded_set_id])) {
        /* test that a NULL set gives the same results as an empty set */
        sel_fb = ucnvsel_open(encodings, num_encodings,
                              NULL,
                              UCNV_ROUNDTRIP_AND_FALLBACK_SET, &status);
      } else {
        sel_fb = ucnvsel_open(encodings, num_encodings,
                              excluded_sets[excluded_set_id],
                              UCNV_ROUNDTRIP_AND_FALLBACK_SET, &status);
      }
      if (U_FAILURE(status)) {
        log_err("ucnv_sel_open(encodings %ld) failed - %s\n", testCaseIdx, u_errorName(status));
        ucnvsel_close(sel_rt);
        uprv_free((void *)encodings);
        continue;
      }

      text_reset(&text);
      for (;;) {
        UBool *manual_rt, *manual_fb;
        static UChar utf16[10000];
        char *s;
        int32_t length8, length16;

        s = text_nextString(&text, &length8);
        if (s == NULL || (getTestOption(QUICK_OPTION) && text.number > 3)) {
          break;
        }

        manual_rt = getResultsManually(encodings, num_encodings,
                                       s, length8,
                                       excluded_sets[excluded_set_id],
                                       UCNV_ROUNDTRIP_SET);
        manual_fb = getResultsManually(encodings, num_encodings,
                                       s, length8,
                                       excluded_sets[excluded_set_id],
                                       UCNV_ROUNDTRIP_AND_FALLBACK_SET);
        /* UTF-8 with length */
        status = U_ZERO_ERROR;
        verifyResult(ucnvsel_selectForUTF8(sel_rt, s, length8, &status), manual_rt);
        verifyResult(ucnvsel_selectForUTF8(sel_fb, s, length8, &status), manual_fb);
        /* UTF-8 NUL-terminated */
        verifyResult(ucnvsel_selectForUTF8(sel_rt, s, -1, &status), manual_rt);
        verifyResult(ucnvsel_selectForUTF8(sel_fb, s, -1, &status), manual_fb);

        u_strFromUTF8(utf16, UPRV_LENGTHOF(utf16), &length16, s, length8, &status);
        if (U_FAILURE(status)) {
          log_err("error converting the test text (string %ld) to UTF-16 - %s\n",
                  (long)text.number, u_errorName(status));
        } else {
          if (text.number == 0) {
            sel_fb = serializeAndUnserialize(sel_fb, &buffer_fb, &status);
          }
          if (U_SUCCESS(status)) {
            /* UTF-16 with length */
            verifyResult(ucnvsel_selectForString(sel_rt, utf16, length16, &status), manual_rt);
            verifyResult(ucnvsel_selectForString(sel_fb, utf16, length16, &status), manual_fb);
            /* UTF-16 NUL-terminated */
            verifyResult(ucnvsel_selectForString(sel_rt, utf16, -1, &status), manual_rt);
            verifyResult(ucnvsel_selectForString(sel_fb, utf16, -1, &status), manual_fb);
          }
        }

        uprv_free(manual_rt);
        uprv_free(manual_fb);
      }
      ucnvsel_close(sel_rt);
      ucnvsel_close(sel_fb);
      uprv_free(buffer_fb);
    }
    uprv_free((void *)encodings);
  }

  releaseAvailableNames();
  text_close(&text);
  for(i = 0 ; i < 3 ; i++) {
    uset_close(excluded_sets[i]);
  }
}