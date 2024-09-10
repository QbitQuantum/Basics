char *   
slipstuff(u_char * buf, unsigned * datalen, unsigned buflen)
{
   u_char * inbuf;
   u_char * outbuf;
   unsigned newlength;
   unsigned dlength;    /* scratch length holder */

   dlength = *datalen;

#ifdef FAST_SLIP
   /* if there are no slip ESCAPE chars, take fast path: */
   if (MEMCHR(buf, SL_ESC, dlength) == NULL)
   {
      if (MEMCHR(buf, SL_END, dlength) == NULL)
      {
         *(buf + dlength) = SL_END; /* new END char at back */
         buf--;
         *buf = SL_END; /* prepend END byte at front */
         *datalen += 2; /* adjust return length for 2 added bytes */
         return (char*)buf;
      }
   }
#endif   /* FAST_SLIP */

   MEMCPY(slipbuf, buf, dlength);      /* make a copy of buffer */
   inbuf = slipbuf;
   *buf = SL_END;    /* start packet with an END char, per RFC 1055 */
   outbuf = buf+1;
   newlength = 1 + dlength;

   while (dlength--)
   {
      switch (*inbuf)
      {
      case SL_END:   /* replace "END" chars with ESC_ENDs */
         *outbuf++ = SL_ESC;
         *outbuf++ = SL_ESC_END;
         newlength += 1;
      break;
      case SL_ESC:   /* replace imbedded escapes with ESC_ESCs */
         *outbuf++ = SL_ESC;
         *outbuf++ = SL_ESC_ESC;
         newlength += 1;
      break;
         default:    /* not a special char, just move it. */
         *outbuf++ = *inbuf;  /* inbuf is bumped below */
      }
      inbuf++;

      /* make sure we don't overwrite end of buffer */
      if (newlength > (buflen - (SLIPHDR_SIZE + SLIPHDR_BIAS + 1)))
      {
#ifdef NPDEBUG
         dprintf("slipstuff overflow: %d\r\n", newlength);
#endif
         return NULL;
      }
   }
   /* now add the END char to end */
   *outbuf = SL_END;
   newlength++;

   *datalen = newlength;   /* return length of "stuffed" packet */
   return (char*)buf;      /* return pointer to packet */
}