void
nsHTMLContentSerializer::AppendAndTranslateEntities(const nsAString& aStr,
                                                     nsAString& aOutputStr)
{
  if (mBodyOnly && !mInBody) {
    return;
  }

  if (mDisableEntityEncoding) {
    aOutputStr.Append(aStr);
    return;
  }

  bool nonBasicEntities =
    !!(mFlags & (nsIDocumentEncoder::OutputEncodeLatin1Entities |
                 nsIDocumentEncoder::OutputEncodeHTMLEntities   |
                 nsIDocumentEncoder::OutputEncodeW3CEntities));

  if (!nonBasicEntities &&
      (mFlags & (nsIDocumentEncoder::OutputEncodeBasicEntities))) {
    const char **entityTable = mInAttribute ? kAttrEntities : kEntities;
    PRUint32 start = 0;
    const PRUint32 len = aStr.Length();
    for (PRUint32 i = 0; i < len; ++i) {
      const char* entity = nsnull;
      i = FindNextBasicEntity(aStr, len, i, entityTable, &entity);
      PRUint32 normalTextLen = i - start; 
      if (normalTextLen) {
        aOutputStr.Append(Substring(aStr, start, normalTextLen));
      }
      if (entity) {
        aOutputStr.AppendASCII(entity);
        start = i + 1;
      }
    }
    return;
  } else if (nonBasicEntities) {
    nsIParserService* parserService = nsContentUtils::GetParserService();

    if (!parserService) {
      NS_ERROR("Can't get parser service");
      return;
    }

    nsReadingIterator<PRUnichar> done_reading;
    aStr.EndReading(done_reading);

    // for each chunk of |aString|...
    PRUint32 advanceLength = 0;
    nsReadingIterator<PRUnichar> iter;

    const char **entityTable = mInAttribute ? kAttrEntities : kEntities;
    nsCAutoString entityReplacement;

    for (aStr.BeginReading(iter);
         iter != done_reading;
         iter.advance(PRInt32(advanceLength))) {
      PRUint32 fragmentLength = iter.size_forward();
      PRUint32 lengthReplaced = 0; // the number of UTF-16 codepoints
                                    //  replaced by a particular entity
      const PRUnichar* c = iter.get();
      const PRUnichar* fragmentStart = c;
      const PRUnichar* fragmentEnd = c + fragmentLength;
      const char* entityText = nsnull;
      const char* fullConstEntityText = nsnull;
      char* fullEntityText = nsnull;

      advanceLength = 0;
      // for each character in this chunk, check if it
      // needs to be replaced
      for (; c < fragmentEnd; c++, advanceLength++) {
        PRUnichar val = *c;
        if (val <= kValNBSP && entityTable[val]) {
          fullConstEntityText = entityTable[val];
          break;
        } else if (val > 127 &&
                  ((val < 256 &&
                    mFlags & nsIDocumentEncoder::OutputEncodeLatin1Entities) ||
                    mFlags & nsIDocumentEncoder::OutputEncodeHTMLEntities)) {
          entityReplacement.Truncate();
          parserService->HTMLConvertUnicodeToEntity(val, entityReplacement);

          if (!entityReplacement.IsEmpty()) {
            entityText = entityReplacement.get();
            break;
          }
        }
        else if (val > 127 &&
                  mFlags & nsIDocumentEncoder::OutputEncodeW3CEntities &&
                  mEntityConverter) {
          if (NS_IS_HIGH_SURROGATE(val) &&
              c + 1 < fragmentEnd &&
              NS_IS_LOW_SURROGATE(*(c + 1))) {
            PRUint32 valUTF32 = SURROGATE_TO_UCS4(val, *(++c));
            if (NS_SUCCEEDED(mEntityConverter->ConvertUTF32ToEntity(valUTF32,
                              nsIEntityConverter::entityW3C, &fullEntityText))) {
              lengthReplaced = 2;
              break;
            }
            else {
              advanceLength++;
            }
          }
          else if (NS_SUCCEEDED(mEntityConverter->ConvertToEntity(val,
                                nsIEntityConverter::entityW3C, 
                                &fullEntityText))) {
            lengthReplaced = 1;
            break;
          }
        }
      }

      aOutputStr.Append(fragmentStart, advanceLength);
      if (entityText) {
        aOutputStr.Append(PRUnichar('&'));
        AppendASCIItoUTF16(entityText, aOutputStr);
        aOutputStr.Append(PRUnichar(';'));
        advanceLength++;
      }
      else if (fullConstEntityText) {
        aOutputStr.AppendASCII(fullConstEntityText);
        ++advanceLength;
      }
      // if it comes from nsIEntityConverter, it already has '&' and ';'
      else if (fullEntityText) {
        AppendASCIItoUTF16(fullEntityText, aOutputStr);
        nsMemory::Free(fullEntityText);
        advanceLength += lengthReplaced;
      }
    }
  } else {
    nsXMLContentSerializer::AppendAndTranslateEntities(aStr, aOutputStr);
  }
}