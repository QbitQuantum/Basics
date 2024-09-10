RT_B RT_API RtDrawImageList(RT_H hImageList, RT_H hDc, RT_N nX, RT_N nY)
{
  RT_N32 nImagesCount;
  RT_N32 nWidth;
  RT_N32 nHeight;
  RT_N nI;
  RT_B bResult;

  nImagesCount = ImageList_GetImageCount(hImageList);
  bResult = ImageList_GetIconSize(hImageList, &nWidth, &nHeight);
  if (bResult)
  {
    for (nI = 0; nI < nImagesCount; nI++)
    {
      bResult = ImageList_Draw(hImageList, nI, hDc, nX + nI * nWidth, nY, ILD_TRANSPARENT);
      if (!bResult)
      {
        break;
      }
    }
  }

  return bResult;
}