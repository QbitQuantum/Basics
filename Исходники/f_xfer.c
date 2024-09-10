word Shall_We_Continue(word timeout, char *do_what)
{
  word pause, ret;
  int ch;

  long tmr;

  ret=TRUE;

  Putc('\n');
  
  Printf(pause_msg, pause=timeout, do_what);
    
  while (pause-- > 0)
  {
    Printf(pause_time, pause);
    
    tmr=timerset(100);

    vbuf_flush();

    while (!timeup(tmr) && !Mdm_keyp())
      Giveaway_Slice();

    if (Mdm_keyp())
    {
      ch=Mdm_getcw();
      
      if (ch=='\x0d')       /* C/R */
        break;
      else if (ch=='\x1b')  /* ESC */
      {
/*        Puts(xferaborted);*/
        ret=FALSE;
        break;
      }
    }
  }

  Puts("\r" CLEOL);
  WhiteN();
  return ret;
}