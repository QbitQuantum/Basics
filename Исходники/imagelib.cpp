void ImageLibrary::drawAlpha(HDC hDC, int index, int x, int y, int width, int height)
{
  Locker lock_(lock);
  if (index <= 0 || index > ilist.length())
    return;
  if (ilist[index]->hAlphaBitmap == NULL)
    ilist[index]->hAlphaBitmap = ilist[index]->image->createAlphaBitmap(hImageDC);
  if (ilist[index]->hAlphaBitmap)
  {
    SelectObject(hImageDC, ilist[index]->hAlphaBitmap);
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;
    bf.AlphaFormat = AC_SRC_ALPHA;
    AlphaBlend(hDC, x, y, width, height, hImageDC, 0, 0, width, height, bf);
  }
  else
    ImageList_DrawEx(list, index, hDC, x, y, width, height, CLR_NONE, CLR_NONE, ILD_NORMAL);
}