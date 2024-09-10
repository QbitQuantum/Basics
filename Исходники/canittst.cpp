void CanonicalIteratorTest::TestBasic() {

    UErrorCode status = U_ZERO_ERROR;

    static const char * const testArray[][2] = {
        {"\\u00C5d\\u0307\\u0327", "A\\u030Ad\\u0307\\u0327, A\\u030Ad\\u0327\\u0307, A\\u030A\\u1E0B\\u0327, "
            "A\\u030A\\u1E11\\u0307, \\u00C5d\\u0307\\u0327, \\u00C5d\\u0327\\u0307, "
            "\\u00C5\\u1E0B\\u0327, \\u00C5\\u1E11\\u0307, \\u212Bd\\u0307\\u0327, "
            "\\u212Bd\\u0327\\u0307, \\u212B\\u1E0B\\u0327, \\u212B\\u1E11\\u0307"},
        {"\\u010d\\u017E", "c\\u030Cz\\u030C, c\\u030C\\u017E, \\u010Dz\\u030C, \\u010D\\u017E"},
        {"x\\u0307\\u0327", "x\\u0307\\u0327, x\\u0327\\u0307, \\u1E8B\\u0327"},
    };
    
#if 0
    // This is not interesting for C/C++ as the data is already built beforehand
    // check build
    UnicodeSet ss = CanonicalIterator.getSafeStart();
    logln("Safe Start: " + ss.toPattern(true));
    ss = CanonicalIterator.getStarts('a');
    expectEqual("Characters with 'a' at the start of their decomposition: ", "", CanonicalIterator.getStarts('a'),
        new UnicodeSet("[\u00E0-\u00E5\u0101\u0103\u0105\u01CE\u01DF\u01E1\u01FB"
        + "\u0201\u0203\u0227\u1E01\u1EA1\u1EA3\u1EA5\u1EA7\u1EA9\u1EAB\u1EAD\u1EAF\u1EB1\u1EB3\u1EB5\u1EB7]")
            );
#endif

    // check permute
    // NOTE: we use a TreeSet below to sort the output, which is not guaranteed to be sorted!

    Hashtable *permutations = new Hashtable(FALSE, status);
    permutations->setValueDeleter(uhash_deleteUnicodeString);
    UnicodeString toPermute("ABC");

    CanonicalIterator::permute(toPermute, FALSE, permutations, status);

    logln("testing permutation");
  
    expectEqual("Simple permutation ", "", collectionToString(permutations), "ABC, ACB, BAC, BCA, CAB, CBA");

    delete permutations;
    
    // try samples
    logln("testing samples");
    Hashtable *set = new Hashtable(FALSE, status);
    set->setValueDeleter(uhash_deleteUnicodeString);
    int32_t i = 0;
    CanonicalIterator it("", status);
    if(U_SUCCESS(status)) {
      for (i = 0; i < ARRAY_LENGTH(testArray); ++i) {
          //logln("Results for: " + name.transliterate(testArray[i]));
          UnicodeString testStr = CharsToUnicodeString(testArray[i][0]);
          it.setSource(testStr, status);
          set->removeAll();
          for (;;) {
              //UnicodeString *result = new UnicodeString(it.next());
              UnicodeString result(it.next());
              if (result.isBogus()) {
                  break;
              }
              set->put(result, new UnicodeString(result), status); // Add result to the table
              //logln(++counter + ": " + hex.transliterate(result));
              //logln(" = " + name.transliterate(result));
          }
          expectEqual(i + ": ", testStr, collectionToString(set), CharsToUnicodeString(testArray[i][1]));

      }
    } else {
      dataerrln("Couldn't instantiate canonical iterator. Error: %s", u_errorName(status));
    }
    delete set;
}