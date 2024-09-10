/******************************************************************************
 * ME_CharFromPointContext
 *
 * Returns a character position inside the run given a run-relative
 * pixel horizontal position.
 *
 * If closest is FALSE return the actual character
 * If closest is TRUE will round to the closest leading edge.
 * ie. if the second character is at pixel position 8 and third at 16 then for:
 * closest = FALSE cx = 0..7 return 0, cx = 8..15 return 1
 * closest = TRUE  cx = 0..3 return 0, cx = 4..11 return 1.
 */
int ME_CharFromPointContext(ME_Context *c, int cx, ME_Run *run, BOOL closest, BOOL visual_order)
{
  ME_String *mask_text = NULL;
  WCHAR *str;
  int fit = 0;
  HGDIOBJ hOldFont;
  SIZE sz, sz2, sz3;
  if (!run->len || cx <= 0)
    return 0;

  if (run->nFlags & (MERF_TAB | MERF_ENDCELL))
  {
    if (!closest || cx < run->nWidth / 2) return 0;
    return 1;
  }

  if (run->nFlags & MERF_GRAPHICS)
  {
    SIZE sz;
    ME_GetOLEObjectSize(c, run, &sz);
    if (!closest || cx < sz.cx / 2) return 0;
    return 1;
  }

  if (run->para->nFlags & MEPF_COMPLEX)
  {
      int cp, trailing;
      if (visual_order && run->script_analysis.fRTL) cx = run->nWidth - cx - 1;

      ScriptXtoCP( cx, run->len, run->num_glyphs, run->clusters, run->vis_attrs, run->advances, &run->script_analysis,
                   &cp, &trailing );
      TRACE("x %d cp %d trailing %d (run width %d) rtl %d log order %d\n", cx, cp, trailing, run->nWidth,
            run->script_analysis.fRTL, run->script_analysis.fLogicalOrder);
      return closest ? cp + trailing : cp;
  }

  if (c->editor->cPasswordMask)
  {
    mask_text = ME_MakeStringR( c->editor->cPasswordMask, run->len );
    str = mask_text->szData;
  }
  else
    str = get_text( run, 0 );

  hOldFont = ME_SelectStyleFont(c, run->style);
  GetTextExtentExPointW(c->hDC, str, run->len,
                        cx, &fit, NULL, &sz);
  if (closest && fit != run->len)
  {
    GetTextExtentPoint32W(c->hDC, str, fit, &sz2);
    GetTextExtentPoint32W(c->hDC, str, fit + 1, &sz3);
    if (cx >= (sz2.cx+sz3.cx)/2)
      fit = fit + 1;
  }

  ME_DestroyString( mask_text );

  ME_UnselectStyleFont(c, run->style, hOldFont);
  return fit;
}