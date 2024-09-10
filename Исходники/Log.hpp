inline std::string NowTime()
{
   const int MAX_LEN = 200;
   char buffer[MAX_LEN];
   if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", buffer, MAX_LEN) == 0) {
      return "Error in NowTime()";
   }

   char result[100];
   static DWORD first = GetTickCount();
   sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000); 
   return result;
}