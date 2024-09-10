int
rd_word_add1 (struct JT *jtl,
	      w_char *pyomi,	/* normal order (not reversed) */
	      int hinsi,
	      w_char *pkanji,	/* normal order (not reversed) */
	      w_char *comment)
{
  struct rind1 *tary;
  int key, key0, keye;
  int serial = jtl->maxserial;
  w_char *tmp = (w_char *) 0;
  struct rind2 *ri2;
  int ind;
  int which;
  w_char *csult;

  w_char yomi[LENGTHYOMI];
  w_char kanji[LENGTHYOMI];

#ifdef  CONVERT_with_SiSheng
  unsigned int sisheng_int;
  char pan_tmp[256];
  w_char pan_yomi[LENGTHYOMI];

  sisheng_int = 0;
  biki_sisheng (pyomi, pan_tmp, yomi);
  sscanf (pan_tmp, "%d", &sisheng_int);
  Strcpy (kanji, pkanji);
#else
# ifdef CONVERT_from_TOP
  Strcpy (yomi, pyomi);
  Strcpy (kanji, pkanji);
# else
  Sreverse (yomi, pyomi);
  Sreverse (kanji, pkanji);
# endif /* CONVERT_from_TOP */
#endif /* CONVERT_with_SiSheng */

  if ((jtl->bufsize_kanji <= jtl->maxkanji + (Strlen (kanji) + Strlen (comment) + Strlen (yomi) + 3) * sizeof (w_char) + 1)
      && (ud_realloc_kanji (jtl) == 0))
    {
      return (-1);
    }
  if (jtl->bufsize_ri1[D_YOMI] <= jtl->maxri1[D_YOMI] + 2
     && rd_realloc_ri1 (jtl, D_YOMI) == 0)
    {
      return (-1);
    }
  if (jtl->bufsize_ri1[D_KANJI] <= jtl->maxri1[D_KANJI] + 2
     && rd_realloc_ri1 (jtl, D_KANJI) == 0)
    {
      return (-1);
    }
  if (jtl->bufsize_serial <= jtl->maxserial + 4
     && ud_realloc_serial (jtl) == 0)
    {
      return (-1);
    }

  ri2 = jtl->ri2;

  tary = jtl->ri1[D_YOMI];
  key = rd_binary_same (tary, yomi, jtl->maxri1[D_YOMI], jtl->ri2, jtl->kanji, D_YOMI);
  if (key != -1)
    {                           /*  Entry with same yomi */
      ind = tary[key].pter;
      while (1)
        {
          w_char kanji1[LENGTHKANJI];
          w_char comment1[LENGTHKANJI];
          if (jtl->hinsi[ind] == hinsi)
            {
              Get_kanji (ri2[ind].kanjipter + jtl->kanji, yomi, Strlen (yomi), kanji1, NULL, comment1);
              if (Strcmp (pkanji, kanji1) == 0)
                {
                  /* Same hinsi, same kanji, same yomi */
                  if (Strcmp (comment, comment1) != 0)
                    {
                      /* set_comment */
                      ri2[ind].kanjipter = jtl->maxkanji;
                      kanjiadd (jtl, pkanji, pyomi, comment);
                    }
                  return (ind);
                }
            }
          if (ri2[ind].next[D_YOMI] == RD_ENDPTR)
            break;
          ind = ri2[ind].next[D_YOMI];
        }
    }
  for (which = 0; which < 2; which++)
    {
      csult = (which == 0) ? yomi : kanji;
      tary = jtl->ri1[which];
      key = rd_binary1 (tary, csult, jtl->maxri1[which], jtl->ri2, jtl->kanji, which);
      if (key >= 0)
        {
          tmp = KANJI_str (ri2[tary[key].pter].kanjipter + jtl->kanji, which);
#ifdef  CONVERT_with_SiSheng
          tmp = biki_sisheng (tmp, pan_tmp, pan_yomi);
#endif
        }
      if (key < 0 || Strcmp (csult, tmp))
        {                       /* No entry with same yomi */
          key += 1;
          for (key0 = key - 1; key0 >= 0; key0 = tary[key0].pter1)
            {
              tmp = KANJI_str (ri2[tary[key0].pter].kanjipter + jtl->kanji, which);
#ifdef  CONVERT_with_SiSheng
              tmp = biki_sisheng (tmp, pan_tmp, pan_yomi);
#endif
              if (Substr (tmp, csult))
                {
                  break;
                }
            }
#ifdef CONVERT_by_STROKE
          if (jtl->bind != NULL)
            b_index_add (jtl, pyomi, serial);
#endif
          rd_make_space (tary, key, jtl, jtl->maxri1[which], which);
          for (keye = key + 1; keye < jtl->maxri1[which]; keye++)
            {
              tmp = KANJI_str (ri2[tary[keye].pter].kanjipter + jtl->kanji, which);
#ifdef  CONVERT_with_SiSheng
              tmp = biki_sisheng (tmp, pan_tmp, pan_yomi);
#endif
              if (!Substr (csult, tmp))
                break;
              if (tary[keye].pter1 == key0)
                tary[keye].pter1 = key;
            }
          tary[key].pter1 = key0;
          ri2[serial].next[which] = RD_ENDPTR;
        }
      else
        {
          ri2[serial].next[which] = tary[key].pter;
        }
      tary[key].pter = serial;
    }
  jtl->maxserial++;
  jtl->maxri2++;
  jtl->gosuu++;
  ri2[serial].kanjipter = jtl->maxkanji;
  jtl->hinsi[serial] = hinsi;
  jtl->hindo[serial] = 0;       /* Hindo is set later on upper module */
#ifdef  CONVERT_with_SiSheng
  jtl->sisheng[serial] = sisheng_int;
#endif
  kanjiadd (jtl, pkanji, pyomi, comment);
  return (serial);
}