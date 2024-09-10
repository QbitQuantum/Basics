static int
hexEveryTimeCatch(uiContext d, int retval, mode_context env)
     /* ARGSUSED */
{
  yomiContext yc = (yomiContext)d->modec;
  static WCHAR_T buf[256];
  /* ??? ¤³¤Î¤è¤¦¤Ê¥Ð¥Ã¥Õ¥¡¤ò¤¤¤í¤¤¤í¤ÊÉôÊ¬¤Ç»ý¤Ä¤Î¤Ï¹¥¤Þ¤·¤¯¤Ê¤¤¤Î¤Ç¡¢
     uiContext ¤Ë¤Þ¤È¤á¤Æ»ý¤Ã¤Æ¶¦Í­¤·¤Æ»È¤Ã¤¿Êý¤¬ÎÉ¤¤ */
  int codelen = d->kanji_status_return->length;

  d->kanji_status_return->info &= ~(KanjiThroughInfo | KanjiEmptyInfo);

  if (codelen >= 0) {
    MBstowcs(buf, HEXPROMPT, 256);
    WStrncpy(buf + HEXPROMPTLEN, d->kanji_status_return->echoStr, codelen);
    d->kanji_status_return->gline.line = buf;
    d->kanji_status_return->gline.length = codelen + HEXPROMPTLEN;
    d->kanji_status_return->gline.revPos =
      d->kanji_status_return->revPos + HEXPROMPTLEN;
    d->kanji_status_return->gline.revLen = d->kanji_status_return->revLen;
    d->kanji_status_return->info |= KanjiGLineInfo;
    echostrClear(d);
    if (codelen == 4) { /* £´Ê¸»ú¤Ë¤Ê¤Ã¤¿¤È¤­¤Ë¤Ï.... */
      if (convertAsHex(d)) {
	yc->allowedChars = CANNA_NOTHING_ALLOWED;
	*(d->kanji_status_return->echoStr = yc->kana_buffer + yc->kEndp + 1)
	  = *(d->buffer_return);
	d->kanji_status_return->revPos = d->kanji_status_return->revLen = 0;
	d->kanji_status_return->length = 1;
	retval = 0;
	if (cannaconf.hexCharacterDefiningStyle != HEX_USUAL) {
	  d->more.todo = 1;
	  d->more.ch = d->ch;
	  d->more.fnum = CANNA_FN_Kakutei;
	}
      }else{
	CannaBeep();
	d->more.todo = 1;
	d->more.ch = d->ch;
	d->more.fnum = CANNA_FN_DeletePrevious;
      }
    }
    else {
      yc->allowedChars = CANNA_ONLY_HEX;
    }
  }
  checkGLineLen(d);
  return retval;
}