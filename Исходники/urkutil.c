extern CharPtr FastaTitle (BioseqPtr bsp, CharPtr pretext, CharPtr posttext)
{
  CharPtr   title = NULL;
  CharPtr   prep, postp, predum = "", postdum = "";
  Char      idbuf[L_ID], defbuf[L_DEF];
  Int4      prelen = 0, postlen = 0;
  SeqIdPtr  sip;

  if (bsp != NULL)
  {
    if ((sip = bsp->id) != NULL)
    {
      if (pretext != NULL)
      {
        prelen = StrLen (pretext);
        prep = pretext;
      }
      else
      {
        prep = predum;
      }
      if (posttext != NULL)
      {
        postlen = StrLen (posttext);
        postp = posttext;
      }
      else
      {
        postp = postdum;
      }
      if ((title = (CharPtr) MemNew (sizeof (Char) * (L_T+prelen+postlen)))
          != NULL)
      {
        switch (sip->choice)
        {
         case SEQID_LOCAL:
          idbuf[0] = '\0';
          if (sip->data.ptrvalue != NULL)
            StrNCpy (idbuf, ((ObjectIdPtr) sip->data.ptrvalue)->str, L_ID-1);
          idbuf[L_ID-1] = '\0';
          break;
         default:
          FastaId (bsp, idbuf, L_ID);
          break;
        }
        FastaDefLine (bsp, defbuf, L_DEF, NULL, NULL, 0);
        sprintf (title, "%s%s %s%s", prep, idbuf, defbuf, postp);
      }
    }
  }
  return title;
}