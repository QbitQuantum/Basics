/** Returns the next character from the input buffer and fills the buffer if it is empty (similar to
 * fgetc()).
 */
static
int my_getc(
   PPOS*                 ppos
   )
{
   assert(ppos      != NULL);
   assert(ppos->fp  != NULL);
   assert(ppos->pos <  LINE_BUF_SIZE);

   if (ppos->buf[ppos->pos] == '\0')
   {
#if 0
      if (NULL == FGETS(ppos->buf, sizeof(ppos->buf), ppos->fp))
         return EOF;
#else
      int len = FREAD(ppos->buf, sizeof(ppos->buf) - 1, ppos->fp);

      if (len <= 0)
         return EOF;

      ppos->buf[len] = '\0';
#endif
      ppos->pos = 0;
   }
   return (unsigned char)ppos->buf[ppos->pos++];
}