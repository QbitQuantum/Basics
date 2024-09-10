bool GetValue(const std::string& sMessage, double& dval)
{
   std::string svalue = ExtractValue(sMessage);
   printf("GetValue(\"%s\", double)\n", sMessage.c_str());
#ifdef WIN32
   _locale_t loc = _create_locale(LC_ALL, "eng");
   char point = '.';
#else
   std::locale loc("");
   char point = std::use_facet<std::numpunct<char> >(loc).decimal_point();
#endif

   for(size_t p=0; p<svalue.length(); p++)
   {
     if (svalue[p] == '.' || svalue[p] == ',')
       svalue[p] = point;
   }

   char *pend;
   const char* szValue = svalue.c_str();

#ifdef WIN32
   double dValue =_strtod_l(szValue, &pend, loc);
#else
   double dValue = strtod(szValue, &pend);
#endif

   // return true only if scan was stopped by spaces, linefeed or the terminating NUL and if the
   // string was not empty to start with
   if (pend != szValue)
   {
      while( *pend!='\0' && (*pend==' '||*pend=='\n')) pend++;
      if (*pend=='\0')
      {
         dval = dValue;
         return true;
      }
   }
   return false;
}