void startSyntaxTree()
{
  int temp = 0;
  openLexFile();
  getNextToken();
  while(!matchToken(PROGRAM))
  {
    getNextToken();
  }
  temp = lookupNumber(PROGRAM);
  addTokens(hand.root, getTokenName(temp), getTokenType(temp));
}