//
//  TestRuleStatus
//      Test word break rule status constants.
//
void RBBIAPITest::TestRuleStatus() {
     UChar str[30];
     //no longer test Han or hiragana breaking here: ruleStatusVec would return nothing
     // changed UBRK_WORD_KANA to UBRK_WORD_IDEO
     u_unescape("plain word 123.45 \\u30a1\\u30a2 ",
              // 012345678901234567  8      9    0      
              //                     Katakana      
                str, 30);
     UnicodeString testString1(str);
     int32_t bounds1[] = {0, 5, 6, 10, 11, 17, 18, 20, 21};
     int32_t tag_lo[]  = {UBRK_WORD_NONE,     UBRK_WORD_LETTER, UBRK_WORD_NONE,    UBRK_WORD_LETTER,
                          UBRK_WORD_NONE,     UBRK_WORD_NUMBER, UBRK_WORD_NONE,
                          UBRK_WORD_IDEO,     UBRK_WORD_NONE};

     int32_t tag_hi[]  = {UBRK_WORD_NONE_LIMIT, UBRK_WORD_LETTER_LIMIT, UBRK_WORD_NONE_LIMIT, UBRK_WORD_LETTER_LIMIT,
                          UBRK_WORD_NONE_LIMIT, UBRK_WORD_NUMBER_LIMIT, UBRK_WORD_NONE_LIMIT,
                          UBRK_WORD_IDEO_LIMIT, UBRK_WORD_NONE_LIMIT};

     UErrorCode status=U_ZERO_ERROR;

     BreakIterator *bi = BreakIterator::createWordInstance(Locale::getEnglish(), status);
     if(U_FAILURE(status)) {
         errcheckln(status, "Fail : in construction - %s", u_errorName(status));
     } else {
         bi->setText(testString1);
         // First test that the breaks are in the right spots.
         doBoundaryTest(*bi, testString1, bounds1);

         // Then go back and check tag values
         int32_t i = 0;
         int32_t pos, tag;
         for (pos = bi->first(); pos != BreakIterator::DONE; pos = bi->next(), i++) {
             if (pos != bounds1[i]) {
                 errln("FAIL: unexpected word break at postion %d", pos);
                 break;
             }
             tag = bi->getRuleStatus();
             if (tag < tag_lo[i] || tag >= tag_hi[i]) {
                 errln("FAIL: incorrect tag value %d at position %d", tag, pos);
                 break;
             }

             // Check that we get the same tag values from getRuleStatusVec()
             int32_t vec[10];
             int t = bi->getRuleStatusVec(vec, 10, status);
             TEST_ASSERT_SUCCESS(status);
             TEST_ASSERT(t==1);
             TEST_ASSERT(vec[0] == tag);
         }
     }
     delete bi;

     // Now test line break status.  This test mostly is to confirm that the status constants
     //                              are correctly declared in the header.
     testString1 =   "test line. \n";
     // break type    s    s     h

     bi = BreakIterator::createLineInstance(Locale::getEnglish(), status);
     if(U_FAILURE(status)) {
         errcheckln(status, "failed to create word break iterator. - %s", u_errorName(status));
     } else {
         int32_t i = 0;
         int32_t pos, tag;
         UBool   success;

         bi->setText(testString1);
         pos = bi->current();
         tag = bi->getRuleStatus();
         for (i=0; i<3; i++) {
             switch (i) {
             case 0:
                 success = pos==0  && tag==UBRK_LINE_SOFT; break;
             case 1:
                 success = pos==5  && tag==UBRK_LINE_SOFT; break;
             case 2:
                 success = pos==12 && tag==UBRK_LINE_HARD; break;
             default:
                 success = FALSE; break;
             }
             if (success == FALSE) {
                 errln("Fail: incorrect word break status or position.  i=%d, pos=%d, tag=%d",
                     i, pos, tag);
                 break;
             }
             pos = bi->next();
             tag = bi->getRuleStatus();
         }
         if (UBRK_LINE_SOFT >= UBRK_LINE_SOFT_LIMIT ||
             UBRK_LINE_HARD >= UBRK_LINE_HARD_LIMIT ||
             (UBRK_LINE_HARD > UBRK_LINE_SOFT && UBRK_LINE_HARD < UBRK_LINE_SOFT_LIMIT)) {
             errln("UBRK_LINE_* constants from header are inconsistent.");
         }
     }
     delete bi;

}