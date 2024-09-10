static int unpackMPCNumber(QChar ch)
////////////////////////////////////
{
  char c = ch.toLatin1();
  if (ch.isDigit())
    return(c - '0');

  return(10 + c - 'A');
}