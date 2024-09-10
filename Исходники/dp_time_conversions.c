time_t average_time (time_t time1, time_t time2)
{
   long double time1_ld = 0;
   long double time2_ld = 0;
   time_t      avg_time = 0L;
   char        msg[200];     /* stderr message */

   /* To avoid overflow, halve first, add, instead of add first, halve */

   time1_ld  = time1 / 2.0;
   time2_ld  = time2 / 2.0;

   avg_time = (time_t) lrintl(time1_ld + time2_ld);

   if(errno == EDOM) /* Domain Error. See man lrintl() */
   {
      sprintf(msg, "%s %s\n",
              "average_time:",
              "lrintl() returns EDOM (Domain Error)");

      RPGC_log_msg(GL_INFO, msg);
      if(DP_LIB002_DEBUG)
         fprintf(stderr, msg);

      return(FUNCTION_FAILED);
   }

   return(avg_time);

} /* end average_time() ===================================== */