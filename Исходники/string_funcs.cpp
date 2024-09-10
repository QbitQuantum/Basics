char* CharArrayAddString(char* pHead, int maxbufsize, char* caBuf, const unsigned int code, const char* str)
{
   const int usedLen = caBuf - pHead;
   const int unusedLen = maxbufsize - usedLen;

   if(pHead == caBuf)
   {
      pHead[0] = CA_SETHEADER(0, code);
   }
   else
   {
      const unsigned int primeHeader = (unsigned int)pHead[0];
      unsigned int numParams = CA_GETNUMPARAMS(primeHeader);
      const unsigned int primeCode = CA_GETCODE(primeHeader);

      caBuf[0] = CA_SETHEADER(numParams, code);
      
      numParams++;
      pHead[0] = CA_SETHEADER(numParams, primeCode);
   }

   STRNCPY((caBuf + 1), (unusedLen - 1), str, (unusedLen - 1));
   
   return CharArrayAddEmptyString(caBuf + 1, unusedLen - 1);
}