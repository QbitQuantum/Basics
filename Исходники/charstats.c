int main(void)
{
  int ret = 0;

  INIT_MACHINE();

  reg_t numCount    = 1;
  reg_t upCount     = 2;
  reg_t lowCount    = 3;
  reg_t specialCount  = 4;
  reg_t otherCount  = 5;
  reg_t spaceCount  = 6;

  MOVIM8(numCount, 0);
  MOVIM8(spaceCount, 0);
  MOVIM8(upCount, 0);
  MOVIM8(lowCount, 0);
  MOVIM8(specialCount, 0);
  MOVIM8(otherCount, 0);

  reg_t numString = 7;
  reg_t upString = 9;
  reg_t lowString = 11;
  reg_t spaceString = 13;
  reg_t specialString = 15;
  reg_t otherString = 17;
  reg_t newlineString = 19;

  MOVIM16(numString, ADDR(0));
  MOVIM16(spaceString, ADDR(16));
  MOVIM16(upString, ADDR(32));
  MOVIM16(lowString, ADDR(48));
  MOVIM16(specialString, ADDR(64));
  MOVIM16(otherString, ADDR(80));
  MOVIM16(newlineString, ADDR(96));


  reg_t i = 21;

  //                                  123456789012
  insertString(numString,     "numbers  = ", i);
  insertString(spaceString,   "spaces   = ", i);
  insertString(upString,      "uppers   = ", i);
  insertString(lowString,     "lowers   = ", i);
  insertString(specialString, "special  = ", i);
  insertString(otherString,   "other    = ", i);

  //endl
  MOVIM8(REG16(newlineString), '\n');
  MOVIM32(REG16(newlineString) + 1, 0);

  ret = getChar(i);
  while (ret != (-1))
  {
    if (isUpLetter(i, i+1))
    {
      INC8(upCount);
    }
    else if (isLowLetter(i, i+1))
    {
      INC8(lowCount);
    }
    else if (isNumber(i, i+1))
    {
      INC8(numCount);
    }
    else if (isSpace(i, i+1))
    {
#ifdef PATCHED
      INC8(spaceCount);
#else
      INC32(spaceCount);
#endif
    }
    else if (isSpecial(i, i+1))
    {
      INC8(specialCount);
    }
    else
    {
      INC8(otherCount);
    }
    printChar(i);
    ret = getChar(i);
  }

  printString(numString, i, i+4);
  printReg8(numCount, i);
  printString(newlineString, i, i+4);

  printString(upString, i, i+4);
  printReg8(upCount, i);
  printString(newlineString, i, i+4);

  printString(lowString, i, i+4);
  printReg8(lowCount, i);
  printString(newlineString, i, i+4);

  printString(spaceString, i, i+4);
  printReg8(spaceCount, i);
  printString(newlineString, i, i+4);

  printString(specialString, i, i+4);
  printReg8(specialCount, i);
  printString(newlineString, i, i+4);

  printString(otherString, i, i+4);
  printReg8(otherCount, i);
  printString(newlineString, i, i+4);

  return (0);
}