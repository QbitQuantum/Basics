static int
hx_get_child_data(hx_logsys_t *log,
                hx_process_t *child,
                unsigned char *buffer,
                long *buflen)
{
   const char    *rname = "hx_get_child_data ()";

   long rem = *buflen;
   long totRead = 0;

   unsigned char *pbuf = buffer;
   unsigned char *errStr;

   int timeout;
   int retval;

#ifdef _HX_WIN32_

   DWORD read = 0;
   HANDLE out;

#elif defined(_HX_UNIX_)

   int out;

#endif

   hx_log_msg(log, HX_LCALL, rname, "Called");

   /* Retrieve the server timeout from the
      config table */
   timeout = atoi((unsigned char *)hx_get_conf_val(log, IDX_SERVER_TIMEOUT));

#ifdef _HX_WIN32_

   out = child->childHandles[HX_STDOUT];

   while(1)
   {
      retval = ReadFile(out, pbuf, rem, &read, NULL);

      if(!retval || read == 0)
      {
         /* End of file Encountered */
         break;
      }

      pbuf += read;
      rem  -= read;
      totRead += read;

      if(rem <= 0)
         return HX_MOREDATA;
   }

#elif defined (_HX_UNIX_)

   out = child->parentStreams[HX_STDOUT];

   while(1)
   {
      retval = hx_readNonBlock(out, timeout, pbuf, rem);

      if(!retval || retval < 0)
      {
         /* End of file Encountered */
         if(retval < 0)
         {
            switch(retval)
            {
               case HX_ERR_CHILDREAD_TIMED_OUT:
                  errStr = "Child process read timed out";
                  break;
               case HX_ERR_CHILDWRITE_TIMED_OUT:
                  errStr = "Child process write timed out";
                  break;
               case HX_ERR_CHILDREAD:
                  errStr = "Error reading from child pipe";
                  break;
               case HX_ERR_IOCTL:
                  errStr = "Error performing ioctl on pipe";
                  break;
               case HX_ERR_SELECT:
                  errStr = "Error performing select";
                  break;
               default:
                  errStr = "Unkown error reading from pipe";
                  break;
            }

            hx_log_msg(log,
                      HX_LERRO,
                      rname,
                      "%s [%s]",
                      errStr,
                      strerror(errno));
         }
         break;
      }

      pbuf += retval;
      rem  -= retval;
      totRead += retval;

      if(rem <= 0)
         return HX_MOREDATA;
   }

#endif

   *buflen = totRead;

   if(!retval)
      return HX_ENDOFDATA;
   else
      return retval;
}