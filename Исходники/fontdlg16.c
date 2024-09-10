/***********************************************************************
 *                FontFamilyEnumProc                     (COMMDLG.19)
 */
INT16 WINAPI FontFamilyEnumProc16( SEGPTR logfont, SEGPTR metrics,
                                   UINT16 nFontType, LPARAM lParam )
{
  HWND hwnd=HWND_32(LOWORD(lParam));
  HWND hDlg=GetParent(hwnd);
  LPCHOOSEFONT16 lpcf;
  LOGFONT16 *lplf = MapSL( logfont );
  TEXTMETRIC16 *lpmtrx16 = MapSL(metrics);
  ENUMLOGFONTEXW elf32w;
  NEWTEXTMETRICEXW nmtrx32w;

  lpcf = (LPCHOOSEFONT16)GetPropW(hDlg, strWineFontData16);
  FONT_LogFont16To32W(lplf, &(elf32w.elfLogFont));
  FONT_Metrics16To32W(lpmtrx16, &nmtrx32w);
  return AddFontFamily(&elf32w, &nmtrx32w, nFontType,
          (LPCHOOSEFONTW)lpcf->lpTemplateName, hwnd,NULL);
}