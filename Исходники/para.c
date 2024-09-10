void ME_MakeFirstParagraph(ME_TextEditor *editor)
{
  ME_Context c;
  CHARFORMAT2W cf;
  LOGFONTW lf;
  HFONT hf;
  ME_TextBuffer *text = editor->pBuffer;
  ME_DisplayItem *para = make_para(editor);
  ME_DisplayItem *run;
  ME_Style *style;
  int eol_len;
  WCHAR cr_lf[] = {'\r','\n',0};

  ME_InitContext(&c, editor, ITextHost_TxGetDC(editor->texthost));

  hf = GetStockObject(SYSTEM_FONT);
  assert(hf);
  GetObjectW(hf, sizeof(LOGFONTW), &lf);
  ZeroMemory(&cf, sizeof(cf));
  cf.cbSize = sizeof(cf);
  cf.dwMask = CFM_BACKCOLOR|CFM_COLOR|CFM_FACE|CFM_SIZE|CFM_CHARSET;
  cf.dwMask |= CFM_ALLCAPS|CFM_BOLD|CFM_DISABLED|CFM_EMBOSS|CFM_HIDDEN;
  cf.dwMask |= CFM_IMPRINT|CFM_ITALIC|CFM_LINK|CFM_OUTLINE|CFM_PROTECTED;
  cf.dwMask |= CFM_REVISED|CFM_SHADOW|CFM_SMALLCAPS|CFM_STRIKEOUT;
  cf.dwMask |= CFM_SUBSCRIPT|CFM_UNDERLINETYPE|CFM_WEIGHT;
  
  cf.dwEffects = CFE_AUTOCOLOR | CFE_AUTOBACKCOLOR;
  lstrcpyW(cf.szFaceName, lf.lfFaceName);
  /* Convert system font height from logical units to twips for cf.yHeight */
  cf.yHeight = (lf.lfHeight * 72 * 1440) / (c.dpi.cy * c.dpi.cy);
  if (lf.lfWeight > FW_NORMAL) cf.dwEffects |= CFE_BOLD;
  cf.wWeight = lf.lfWeight;
  if (lf.lfItalic) cf.dwEffects |= CFE_ITALIC;
  cf.bUnderlineType = (lf.lfUnderline) ? CFU_CF1UNDERLINE : CFU_UNDERLINENONE;
  if (lf.lfStrikeOut) cf.dwEffects |= CFE_STRIKEOUT;
  cf.bPitchAndFamily = lf.lfPitchAndFamily;
  cf.bCharSet = lf.lfCharSet;

  style = ME_MakeStyle(&cf);
  text->pDefaultStyle = style;

  eol_len = editor->bEmulateVersion10 ? 2 : 1;
  para->member.para.text = ME_MakeStringN( cr_lf, eol_len );

  run = ME_MakeRun(style, MERF_ENDPARA);
  run->member.run.nCharOfs = 0;
  run->member.run.len = eol_len;
  run->member.run.para = &para->member.para;

  ME_InsertBefore(text->pLast, para);
  ME_InsertBefore(text->pLast, run);
  para->member.para.prev_para = text->pFirst;
  para->member.para.next_para = text->pLast;
  text->pFirst->member.para.next_para = para;
  text->pLast->member.para.prev_para = para;

  text->pLast->member.para.nCharOfs = editor->bEmulateVersion10 ? 2 : 1;

  ME_DestroyContext(&c);
}