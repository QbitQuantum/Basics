// internal function
void dnm_cli_printf_v (const char *format, va_list arg)
{
   static  BOOLEAN  wasError = FALSE;

   INT32S  len, hdrLen;
   INT32S  res;
   char    buf[DN_CLI_CTRL_SIZE];
   BOOLEAN prevVal;
   CS_LOCAL_VAR;

//   ((dn_cli_ctrlMsg_t *)buf)->cmdId   = DN_CLI_CMD_TYPE_TRACE;
#ifdef WIN32
   if (dnm_cli_v.pCliLogFile != NULL) vfprintf(dnm_cli_v.pCliLogFile, format, arg);
#endif
   
//   hdrLen = sizeof(dn_cli_ctrlMsg_t);
   hdrLen = 0;

   if (wasError) {   // Add "..."
      SNPRINTF(buf + hdrLen, sizeof(buf) - hdrLen, ERR_INDICATOR);
      hdrLen += strlen(ERR_INDICATOR);
   }

   len = VSPRINTF(buf + hdrLen, sizeof(buf) - hdrLen, format, arg);
   if(len < 0)   // error - print '***********'
      len = SNPRINTF(buf + hdrLen, sizeof(buf) - hdrLen, "*** CLI_LEN_ERROR ***\r\n");
   buf[sizeof(buf)-1] = 0;
   len += hdrLen;
   if (len>sizeof(buf)) 
      len = sizeof(buf);  
   
   prevVal = wasError;
   res = dn_write(DN_CLI_DEV_ID, buf, len);

   OS_ENTER_CRITICAL();
   if (res == DN_ERR_NO_RESOURCES || (!prevVal && wasError))
      wasError = TRUE;
   else
      wasError = FALSE;
   OS_EXIT_CRITICAL();
}