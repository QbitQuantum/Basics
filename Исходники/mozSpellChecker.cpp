NS_IMETHODIMP
mozSpellChecker::Replace(const nsAString &aOldWord, const nsAString &aNewWord, bool aAllOccurrences)
{
  if(!mConverter)
    return NS_ERROR_NULL_POINTER;

  nsAutoString newWord(aNewWord); // sigh

  if(aAllOccurrences){
    int32_t selOffset;
    int32_t startBlock,currentBlock,currOffset;
    int32_t begin,end;
    bool done;
    nsresult result;
    nsAutoString str;

    // find out where we are
    result = SetupDoc(&selOffset);
    if(NS_FAILED(result))
      return result;
    result = GetCurrentBlockIndex(mTextServicesDocument,&startBlock);
    if(NS_FAILED(result))
      return result;

    //start at the beginning
    result = mTextServicesDocument->FirstBlock();
    currOffset=0;
    currentBlock = 0;
    while (NS_SUCCEEDED(mTextServicesDocument->IsDone(&done)) && !done) {
      result = mTextServicesDocument->GetCurrentTextBlock(&str);
      do {
        result = mConverter->FindNextWord(str.get(),str.Length(),currOffset,&begin,&end);
        if (NS_SUCCEEDED(result) && (begin != -1)) {
          if (aOldWord.Equals(Substring(str, begin, end-begin))) {
            // if we are before the current selection point but in the same
            // block move the selection point forwards
            if (currentBlock == startBlock && begin < selOffset) {
              selOffset +=
                int32_t(aNewWord.Length()) - int32_t(aOldWord.Length());
              if (selOffset < begin) {
                selOffset=begin;
              }
            }
            mTextServicesDocument->SetSelection(begin, end-begin);
            mTextServicesDocument->InsertText(&newWord);
            mTextServicesDocument->GetCurrentTextBlock(&str);
            end += (aNewWord.Length() - aOldWord.Length());  // recursion was cute in GEB, not here.
          }
        }
        currOffset = end;
      } while(currOffset != -1);
      mTextServicesDocument->NextBlock();
      currentBlock++;
      currOffset=0;
    }

    // We are done replacing.  Put the selection point back where we found  it (or equivalent);
    result = mTextServicesDocument->FirstBlock();
    currentBlock = 0;
    while(NS_SUCCEEDED(mTextServicesDocument->IsDone(&done)) && !done &&
          currentBlock < startBlock) {
      mTextServicesDocument->NextBlock();
    }

//After we have moved to the block where the first occurrence of replace was done, put the
//selection to the next word following it. In case there is no word following it i.e if it happens
//to be the last word in that block, then move to the next block and put the selection to the
//first word in that block, otherwise when the Setupdoc() is called, it queries the LastSelectedBlock()
//and the selection offset of the last occurrence of the replaced word is taken instead of the first
//occurrence and things get messed up as reported in the bug 244969

    if (NS_SUCCEEDED(mTextServicesDocument->IsDone(&done)) && !done){
      nsString str;
      result = mTextServicesDocument->GetCurrentTextBlock(&str);
      result = mConverter->FindNextWord(str.get(),str.Length(),selOffset,&begin,&end);
      if (end == -1) {
        mTextServicesDocument->NextBlock();
        selOffset=0;
        result = mTextServicesDocument->GetCurrentTextBlock(&str);
        result = mConverter->FindNextWord(str.get(),str.Length(),selOffset,&begin,&end);
        mTextServicesDocument->SetSelection(begin, 0);
      } else {
        mTextServicesDocument->SetSelection(begin, 0);
      }
    }
  } else {
    mTextServicesDocument->InsertText(&newWord);
  }
  return NS_OK;
}