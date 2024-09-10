bool Balloon::DrawAlphaBlend()
{
  RECT clientrt, contentrt;
  POINT srcPt;
  SIZE wndSz;
  BLENDFUNCTION bf;
  CLIENTINFO clientInfo;
  FORMATINFO formatInfo;
  int alpha = (pSettings->GetAlpha() * 255) / 100;

  if (!GetClientRect(balloonWnd, &clientrt))
  {
    return false;
  }

  HDC hdc = CreateCompatibleDC(NULL);
  HBITMAP hbitmap = EGCreateBitmap(0x00, RGB(0, 0, 0), clientrt);
  HGDIOBJ hobj = SelectObject(hdc, hbitmap);

  CopyRect(&contentrt, &clientrt);
  EGFrameRect(hdc, &contentrt, 255, pSettings->GetBorderColor(), 1);
  InflateRect(&contentrt, -1, -1);
  if (ELToLower(pSettings->GetGradientMethod()) == TEXT("solid"))
  {
    EGFillRect(hdc, &clientrt, alpha, pSettings->GetGradientFrom());
  }
  else
    EGGradientFillRect(hdc, &contentrt, alpha, pSettings->GetGradientFrom(),
                       pSettings->GetGradientTo(), 0, pSettings->GetGradientMethod());

  formatInfo.horizontalAlignment = EGDAT_LEFT;
  formatInfo.verticalAlignment = EGDAT_TOP;
  formatInfo.font = CreateFontIndirect(pSettings->GetInfoFont());
  formatInfo.color = pSettings->GetTextColor();
  formatInfo.flags = DT_WORDBREAK;
  clientInfo.hdc = hdc;
  CopyRect(&clientInfo.rt, &infoRect);
  clientInfo.bgAlpha = alpha;
  EGDrawAlphaText(255, clientInfo, formatInfo, info);
  DeleteObject(formatInfo.font);

  formatInfo.font = CreateFontIndirect(pSettings->GetInfoTitleFont());
  formatInfo.flags = DT_SINGLELINE;
  CopyRect(&clientInfo.rt, &titleRect);
  EGDrawAlphaText(255, clientInfo, formatInfo, infoTitle);
  DeleteObject(formatInfo.font);

  if (icon)
  {
    DrawIconEx(hdc, 5, 5, icon, iconWidth, iconHeight, 0, NULL, DI_NORMAL);
  }

  bf.BlendOp = AC_SRC_OVER;
  bf.BlendFlags = 0;
  bf.AlphaFormat = AC_SRC_ALPHA;  // use source alpha
  bf.SourceConstantAlpha = 255;

  wndSz.cx = clientrt.right;
  wndSz.cy = clientrt.bottom;
  srcPt.x = 0;
  srcPt.y = 0;

  UpdateLayeredWindow(balloonWnd, NULL, NULL, &wndSz, hdc, &srcPt, 0, &bf, ULW_ALPHA);

  // do cleanup
  SelectObject(hdc, hobj);
  DeleteDC(hdc);
  DeleteObject(hbitmap);

  return true;
}