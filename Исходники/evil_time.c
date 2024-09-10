struct tm *
evil_localtime_r(const time_t *timep, struct tm *result)
{
   __time64_t t = *timep;

   _localtime64_s(result, &t);

   return result;
}