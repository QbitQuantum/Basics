char* dStrlwr(char *str)
{
#if defined(TORQUE_OS_WIN) || defined(TORQUE_OS_XBOX) || defined(TORQUE_OS_XENON)
   return _strlwr(str);
#else
   if (str == NULL)
      return(NULL);

   char* saveStr = str;
   while (*str)
   {
      *str = tolower(*str);
      str++;
   }
   return saveStr;
#endif
}