UtlBoolean SipRedirectorGateway::prefixIsValid(UtlString& p)
{
   int len, digits;
   char last;

   return
      (len = mPrefix.length(),
       // Initial 'len' chars must be the prefix.
       strncmp(p.data(), mPrefix.data(), len) == 0 &&
       (digits = strspn(p.data() + len, "0123456789"),
        // Remaining chars must be digits.
        p.length() == len + digits &&
        (last = p.length(len - 1),
         // Last digit must be 1-9.
         last >= 1)));
}