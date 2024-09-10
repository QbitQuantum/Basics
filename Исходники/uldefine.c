static
int uuTMakeDicYesCatch(uiContext d, int retval, mode_context env)
/* ARGSUSED */
{
  int err = 0, perr = 0;
  tourokuContext tc;
  WCHAR_T **dp;
  extern int defaultContext;

  popCallback(d); /* yesNo ¤ò¥Ý¥Ã¥× */

  tc = (tourokuContext)d->modec;

  if(defaultContext < 0) {
    if((KanjiInit() < 0) || (defaultContext < 0)) {
      jrKanjiError = KanjiInitError();
      freeAndPopTouroku(d);
      defineEnd(d);
      return(GLineNGReturn(d));
    }
  }
  /* ¼­½ñ¤òºî¤ë */
  if (RkwCreateDic(defaultContext, tc->newDic->name, 0x80) < 0) {
    err++; if (errno == EPIPE) perr++;
    MBstowcs(d->genbuf, "\274\255\275\361\244\316\300\270\300\256\244\313"
	"\274\272\307\324\244\267\244\336\244\267\244\277", 256);
                          /* ¼­½ñ¤ÎÀ¸À®¤Ë¼ºÇÔ¤·¤Þ¤·¤¿ */
  } else if(RkwMountDic(defaultContext, tc->newDic->name, 0) < 0) {
    err++; if (errno == EPIPE) perr++;
    MBstowcs(d->genbuf, "\274\255\275\361\244\316\245\336\245\246\245\363"
	"\245\310\244\313\274\272\307\324\244\267\244\336\244\267\244\277", 256);
                          /* ¼­½ñ¤Î¥Þ¥¦¥ó¥È¤Ë¼ºÇÔ¤·¤Þ¤·¤¿ */ 
  } else if(d->contextCache != -1 && 
    RkwMountDic(d->contextCache, tc->newDic->name, 0) < 0) {
    err++; if (errno == EPIPE) perr++;
    MBstowcs(d->genbuf, "\274\255\275\361\244\316\245\336\245\246\245\363"
	"\245\310\244\313\274\272\307\324\244\267\244\336\244\267\244\277", 256);
                          /* ¼­½ñ¤Î¥Þ¥¦¥ó¥È¤Ë¼ºÇÔ¤·¤Þ¤·¤¿ */
  }

  if(err) {
    if (perr) {
      jrKanjiPipeError();
    }
    makeGLineMessage(d, d->genbuf, WStrlen(d->genbuf));
    freeAndPopTouroku(d);
    defineEnd(d);
    currentModeInfo(d);
    return(0);
  }

  tc->newDic->dicflag = DIC_MOUNTED;

  /* ¼­½ñ¤Î¸õÊä¤ÎºÇ¸å¤ËÄÉ²Ã¤¹¤ë */
  dp = tc->udic;
  if (dp) {
    while (*dp) {
      dp++;
    }
    *dp++ = WString(tc->newDic->name);
    *dp = 0;
  }

  return(dicTourokuTango(d, uuTTangoQuitCatch));
}