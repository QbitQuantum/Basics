// ComResWords::isSqlReservedWord() ================================
// Determine if the given word is a reserved identifier.
// =================================================================
//
NABoolean
ComResWords::isSqlReservedWord(const char *word,NABoolean mp_context,
			       UInt32 ifSetFlags)
{
  // no reserved words in mode_special_4
  if ((ifSetFlags & MODE_SPECIAL_4_) != 0)
    return FALSE;

  char uword[MAX_RESWORD_LENGTH];

  NABoolean lookup = TRUE;
  UInt32 i = 0; 
  while (word[i]) {
    if(i >= (MAX_RESWORD_LENGTH - 1)) {
      lookup = FALSE;
      break;
    }
    // Upper case all words since all the words in the resword table
    // are also uppercase.
    //
#pragma nowarn(1506)   // warning elimination 
    uword[i] = TOUPPER(word[i]);
#pragma warn(1506)  // warning elimination 
    i++;
  }
  uword[i] = '\0';

  if (lookup) {
    // search for uppercase word in the reserved word table
    //
    ComResWord resWord = { uword, 0 };
    //resWord.setResWord(uword, 0);
    ComResWord *entry = searchResWordTbl(&resWord);

    return (entry && entry->isReserved(mp_context,ifSetFlags));
  } else {
    return FALSE;
  }
}