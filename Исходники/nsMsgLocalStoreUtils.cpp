void nsMsgLocalStoreUtils::ChangeKeywordsHelper(
    nsIMsgDBHdr *message, uint64_t desiredOffset,
    nsLineBuffer<char> *lineBuffer, nsTArray<nsCString> &keywordArray,
    bool aAdd, nsIOutputStream *outputStream, nsISeekableStream *seekableStream,
    nsIInputStream *inputStream) {
  uint32_t bytesWritten;

  for (uint32_t i = 0; i < keywordArray.Length(); i++) {
    nsAutoCString header;
    nsAutoCString keywords;
    bool done = false;
    uint32_t len = 0;
    nsAutoCString keywordToWrite(" ");

    keywordToWrite.Append(keywordArray[i]);
    seekableStream->Seek(nsISeekableStream::NS_SEEK_SET, desiredOffset);
    // need to reset lineBuffer, which is cheaper than creating a new one.
    lineBuffer->start = lineBuffer->end = lineBuffer->buf;
    bool inKeywordHeader = false;
    bool foundKeyword = false;
    int64_t offsetToAddKeyword = 0;
    bool more;
    message->GetMessageSize(&len);
    // loop through
    while (!done) {
      int64_t lineStartPos;
      seekableStream->Tell(&lineStartPos);
      // we need to adjust the linestart pos by how much extra the line
      // buffer has read from the stream.
      lineStartPos -= (lineBuffer->end - lineBuffer->start);
      // NS_ReadLine doesn't return line termination chars.
      nsCString keywordHeaders;
      nsresult rv = NS_ReadLine(inputStream, lineBuffer, keywordHeaders, &more);
      if (NS_SUCCEEDED(rv)) {
        if (keywordHeaders.IsEmpty())
          break;  // passed headers; no x-mozilla-keywords header; give up.
        if (StringBeginsWith(keywordHeaders,
                             NS_LITERAL_CSTRING(HEADER_X_MOZILLA_KEYWORDS)))
          inKeywordHeader = true;
        else if (inKeywordHeader && (keywordHeaders.CharAt(0) == ' ' ||
                                     keywordHeaders.CharAt(0) == '\t'))
          ;  // continuation header line
        else if (inKeywordHeader)
          break;
        else
          continue;
        uint32_t keywordHdrLength = keywordHeaders.Length();
        int32_t startOffset, keywordLength;
        // check if we have the keyword
        if (MsgFindKeyword(keywordArray[i], keywordHeaders, &startOffset,
                           &keywordLength)) {
          foundKeyword = true;
          if (!aAdd)  // if we're removing, remove it, and break;
          {
            keywordHeaders.Cut(startOffset, keywordLength);
            for (int32_t j = keywordLength; j > 0; j--)
              keywordHeaders.Append(' ');
            seekableStream->Seek(nsISeekableStream::NS_SEEK_SET, lineStartPos);
            outputStream->Write(keywordHeaders.get(), keywordHeaders.Length(),
                                &bytesWritten);
          }
          offsetToAddKeyword = 0;
          // if adding and we already have the keyword, done
          done = true;
          break;
        }
        // argh, we need to check all the lines to see if we already have the
        // keyword, but if we don't find it, we want to remember the line and
        // position where we have room to add the keyword.
        if (aAdd) {
          nsAutoCString curKeywordHdr(keywordHeaders);
          // strip off line ending spaces.
          curKeywordHdr.Trim(" ", false, true);
          if (!offsetToAddKeyword &&
              curKeywordHdr.Length() + keywordToWrite.Length() <
                  keywordHdrLength)
            offsetToAddKeyword = lineStartPos + curKeywordHdr.Length();
        }
      }
    }
    if (aAdd && !foundKeyword) {
      if (!offsetToAddKeyword)
        message->SetUint32Property("growKeywords", 1);
      else {
        seekableStream->Seek(nsISeekableStream::NS_SEEK_SET,
                             offsetToAddKeyword);
        outputStream->Write(keywordToWrite.get(), keywordToWrite.Length(),
                            &bytesWritten);
      }
    }
  }
}