void 
IntlTestCollator::doTestVariant(Collator* col, const UnicodeString &source, const UnicodeString &target, Collator::EComparisonResult result)
{   
  UErrorCode status = U_ZERO_ERROR;

  UCollator *myCollation = col->toUCollator();

  Collator::EComparisonResult compareResult = col->compare(source, target);

  CollationKey srckey, tgtkey;
  col->getCollationKey(source, srckey, status);
  col->getCollationKey(target, tgtkey, status);
  if (U_FAILURE(status)){
    errln("Creation of collation keys failed\n");
  }
  Collator::EComparisonResult keyResult = srckey.compareTo(tgtkey);

  reportCResult(source, target, srckey, tgtkey, compareResult, keyResult, result, result);

    UColAttributeValue norm = ucol_getAttribute(myCollation, UCOL_NORMALIZATION_MODE, &status);

    int32_t sLen = source.length(), tLen = target.length();
    const UChar* src = source.getBuffer();
    const UChar* trg = target.getBuffer();
    UCollationResult compareResultIter = (UCollationResult)result;

    {
      UCharIterator sIter, tIter;
      uiter_setString(&sIter, src, sLen);
      uiter_setString(&tIter, trg, tLen);
      compareResultIter = ucol_strcollIter(myCollation, &sIter, &tIter, &status);
      if(compareResultIter != (UCollationResult)result) {
        errln("Different result for iterative comparison "+source+" "+target);
      }
    }
    /* convert the strings to UTF-8 and do try comparing with char iterator */
    if(!quick) { /*!QUICK*/
      char utf8Source[256], utf8Target[256];
      int32_t utf8SourceLen = 0, utf8TargetLen = 0;
      u_strToUTF8(utf8Source, 256, &utf8SourceLen, src, sLen, &status);
      if(U_FAILURE(status)) { /* probably buffer is not big enough */
        log("Src UTF-8 buffer too small! Will not compare!\n");
      } else {
        u_strToUTF8(utf8Target, 256, &utf8TargetLen, trg, tLen, &status);
        if(U_SUCCESS(status)) { /* probably buffer is not big enough */
          UCollationResult compareResultUTF8 = (UCollationResult)result, compareResultUTF8Norm = (UCollationResult)result;
          UCharIterator sIter, tIter;
          /*log_verbose("Strings converted to UTF-8:%s, %s\n", aescstrdup(source,-1), aescstrdup(target,-1));*/
          uiter_setUTF8(&sIter, utf8Source, utf8SourceLen);
          uiter_setUTF8(&tIter, utf8Target, utf8TargetLen);
       /*uiter_setString(&sIter, source, sLen);
      uiter_setString(&tIter, target, tLen);*/
          compareResultUTF8 = ucol_strcollIter(myCollation, &sIter, &tIter, &status);
          ucol_setAttribute(myCollation, UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
          sIter.move(&sIter, 0, UITER_START);
          tIter.move(&tIter, 0, UITER_START);
          compareResultUTF8Norm = ucol_strcollIter(myCollation, &sIter, &tIter, &status);
          ucol_setAttribute(myCollation, UCOL_NORMALIZATION_MODE, norm, &status);
          if(compareResultUTF8 != compareResultIter) {
            errln("different results in iterative comparison for UTF-16 and UTF-8 encoded strings. "+source+", "+target);
          }
          if(compareResultUTF8 != compareResultUTF8Norm) {
            errln("different results in iterative when normalization is turned on with UTF-8 strings. "+source+", "+target);
          }
        } else {
          log("Target UTF-8 buffer too small! Did not compare!\n");
        }
        if(U_FAILURE(status)) {
          log("UTF-8 strcoll failed! Ignoring result\n");
        }
      }
    }

    /* testing the partial sortkeys */
    { /*!QUICK*/
      int32_t partialSizes[] = { 3, 1, 2, 4, 8, 20, 80 }; /* just size 3 in the quick mode */
      int32_t partialSizesSize = 1;
      if(!quick) {
        partialSizesSize = 7;
      }
      int32_t i = 0;
      log("partial sortkey test piecesize=");
      for(i = 0; i < partialSizesSize; i++) {
        UCollationResult partialSKResult = (UCollationResult)result, partialNormalizedSKResult = (UCollationResult)result;
        log("%i ", partialSizes[i]);

        partialSKResult = compareUsingPartials(myCollation, src, sLen, trg, tLen, partialSizes[i], status);
        if(partialSKResult != (UCollationResult)result) {
          errln("Partial sortkey comparison returned wrong result: "+source+", "+target+" (size "+partialSizes[i]+")");           
        }

        if(norm != UCOL_ON && !quick) {
          log("N ");
          ucol_setAttribute(myCollation, UCOL_NORMALIZATION_MODE, UCOL_ON, &status);
          partialNormalizedSKResult = compareUsingPartials(myCollation, src, sLen, trg, tLen, partialSizes[i], status);
          ucol_setAttribute(myCollation, UCOL_NORMALIZATION_MODE, norm, &status);
          if(partialSKResult != partialNormalizedSKResult) {
            errln("Partial sortkey comparison gets different result when normalization is on: "+source+", "+target+" (size "+partialSizes[i]+")");           
          }
        }
      }
      log("\n");
    }
/*
  if (compareResult != result) {
    errln("String comparison failed in variant test\n");
  }
  if (keyResult != result) {
    errln("Collation key comparison failed in variant test\n");
  }
*/
}