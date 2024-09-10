/*	Output a line
**	-------------
*/
PRIVATE void display_line (HText * text, HTLine * line)
{
#ifdef CURSES
      int     y, x;

      waddstr(w_text, SPACES(line->offset));
      waddstr(w_text, line->data);
      getyx(w_text, y, x);
      if (y < DISPLAY_LINES-1) {
              wmove(w_text, ++y, 0);
      }
#else
   if (!text->target)
   {
#ifdef CYRILLIC
       /* HWL 18/7/94: applied patch from [email protected] (Anton Tropashko) */
       a_print(SPACES(line->offset),H,stdout); 
       a_print(line->data,H,stdout);
       fputc('\n',stdout);
#else
       OutputData(LineMode_getView(text->pLm), "%s%s\n", SPACES(line->offset), line->data);
#endif
   }
   else {
       PUTS(SPACES(line->offset));
       PUTS(line->data);
       PUTC('\n');
   }
#endif
   
}