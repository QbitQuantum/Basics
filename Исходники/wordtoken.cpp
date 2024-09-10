void WordToken::SetFirstInSentence(bool b) {
  //  std::cout << "sf " << string << std::endl;
  char st[MAX_WORD_LENGTH];
  firstInSentence = b;
  if (b) {
    if (IsUpper(*string)) 
      return;
    *st = Upper(*string);
  } else {
    if (IsLower(*string))
      return;
    *st = Lower(*string);
  }
  strcpy(st+1, string+1);      
  SetWord(word, st, token);
}