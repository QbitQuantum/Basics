bool IGraphics::DrawIText(IText* pTxt, char* str, IRECT* pR, bool measure)
{
  if (!str || str[0] == '\0')
  {
    return true;
  }

  LICE_IFont* font = pTxt->mCached;
  
  if (!font)
  {
    font = CacheFont(pTxt);
    if (!font) return false;
  }

  LICE_pixel color = LiceColor(&pTxt->mColor);
  font->SetTextColor(color);

#ifdef OS_WIN
  UINT fmt = DT_NOCLIP;
#else
  // OS X doesn't have an ellipsis option. So we need another way to prevent
  // the text from leaving the rectangle.
  UINT fmt = 0;
#endif
  if (LICE_GETA(color) < 255) fmt |= LICE_DT_USEFGALPHA;
  if (pTxt->mAlign == IText::kAlignNear)
    fmt |= DT_LEFT;
  else if (pTxt->mAlign == IText::kAlignCenter)
    fmt |= DT_CENTER;
  else // if (pTxt->mAlign == IText::kAlignFar)
    fmt |= DT_RIGHT;

  // Crop text on Windows if too long
  if (!measure) {
	  fmt |= DT_END_ELLIPSIS;
  }

  if (measure) 
  {
    fmt |= DT_CALCRECT;
    RECT R = {0,0,0,0};
    font->DrawText(mDrawBitmap, str, -1, &R, fmt);
    
    if( pTxt->mAlign == IText::kAlignNear)
    {
      pR->R = R.right;
    }
    else if (pTxt->mAlign == IText::kAlignCenter)
    {
      pR->L = (int) pR->MW() - (R.right/2);
      pR->R = pR->L + R.right;
    }
    else // (pTxt->mAlign == IText::kAlignFar)
    {
      pR->L = pR->R - R.right;
      pR->R = pR->L + R.right;
    }
    
    pR->B = pR->T + R.bottom;
  }
  else 
  {
    RECT R = { pR->L, pR->T, pR->R, pR->B };
    font->DrawText(mDrawBitmap, str, -1, &R, fmt);
  }

  return true;
}