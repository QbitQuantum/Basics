unsigned int isread(char UUFAR *buffer,
                    unsigned int wanted,
                    unsigned int timeout)
{
   union REGS rcvregs, outregs;
   time_t quit = time( NULL ) + timeout;

   size_t commBufferCached = commBufferUsed;

   if ( wanted > commBufferLength )
   {
      printmsg(0,"nsread: Overlength read, wanted %u bytes into %u buffer!",
                     (unsigned int) wanted,
                     (unsigned int) commBufferLength );
      panic();
   }

#ifdef ARTICOMM_INT14   /* Richard H. Gumpertz ([email protected]), 28 Sep 1993 */
   union REGS timregs;          /* Scratch area for interrupt calls. */

   timregs.x.ax = 0x8009;               /* Set timeouts */
   timregs.x.cx = timeout * 91 / 5;     /* Receive timeout in ticks */
   timregs.x.bx = 0x7FFF/*???*/;        /* Send timeout in ticks */
   timregs.x.dx = portNum;              /* Port number */
   int86(0x14, &timregs, &outregs);
#endif /* ARTICOMM_INT14 */

   rcvregs.h.ah = FS_RECV1;
   rcvregs.h.al = 0;
   rcvregs.x.dx = portNum;              /* Port number */
   rcvregs.x.bx = 0;

   while (commBufferUsed < wanted)
   {
      if ( terminate_processing )
      {
         static KWBoolean recurse = KWFalse;
         if ( ! recurse )
         {
            printmsg(2,"isread: User aborted processing");
            recurse = KWTrue;
         }
         commBufferUsed = 0;
         return commBufferUsed;
      }

      int86(0x14, &rcvregs, &outregs);
      if (!(outregs.h.ah & 0x80))
         commBuffer[commBufferUsed++] = (char) outregs.h.al;
      else {                                 /* the read timed out */
         if (timeout == 0)              /* If not interested in waiting */
            return commBufferUsed;      /* then get out of here fast */

         ShowModem();                   /* Report modem status */

         if ( time(NULL) >= quit )
         {
            printmsg(20, "isread: Timeout (timeout=%u, want=%u, have=%u)",
                          timeout, wanted, commBufferUsed);
            return commBufferUsed;
         }

#ifdef ARTICOMM_INT14 /* Richard H. Gumpertz ([email protected]), 28 Sep 1993 */
         timregs.x.cx = (unsigned short)(quit - now) * 91 / 5; /* Receive timeout in ticks */
         int86(0x14, &timregs, &outregs);
#endif /* ARTICOMM_INT14 */

      } /* else */
   } /* while (commBufferUsed < wanted) */

   traceData( commBuffer + commBufferCached,
              commBufferUsed - commBufferCached,
              KWFalse );

   if ( buffer != NULL )
   {
      MEMCPY(buffer, commBuffer, wanted);
      commBufferUsed -= wanted;
      if (commBufferUsed)
         MEMMOVE(commBuffer, commBuffer + wanted, commBufferUsed);
   }

   return wanted + commBufferUsed;

} /* isread */