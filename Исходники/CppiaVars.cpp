CppiaVar::Access CppiaVar::getAccess(CppiaStream &stream)
{
   std::string tok = stream.getToken();
   if (tok.size()!=1)
      throw "bad var access length";
   switch(tok[0])
   {
      case 'N': return accNormal;
      case 'n': return accNo;
      case 'R': return accResolve;
      case 'C': return accCall;
      case 'V': return accCallNative;
   }
   throw "bad access code";
   return accNormal;
}