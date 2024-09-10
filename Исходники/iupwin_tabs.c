static int winTabsGetImageIndex(Ihandle* ih, const char* name)
{
  HIMAGELIST image_list;
  int count, i, bpp, ret;
  Iarray* bmp_array;
  HBITMAP *bmp_array_data, hMask=NULL;
  HBITMAP bmp = iupImageGetImage(name, ih, 0);
  if (!bmp)
    return -1;

  /* the array is used to avoi adding the same bitmap twice */
  bmp_array = (Iarray*)iupAttribGet(ih, "_IUPWIN_BMPARRAY");
  if (!bmp_array)
  {
    /* create the array if does not exist */
    bmp_array = iupArrayCreate(50, sizeof(HBITMAP));
    iupAttribSetStr(ih, "_IUPWIN_BMPARRAY", (char*)bmp_array);
  }

  bmp_array_data = iupArrayGetData(bmp_array);

  image_list = (HIMAGELIST)SendMessage(ih->handle, TCM_GETIMAGELIST, 0, 0);
  if (!image_list)
  {
    int width, height;
    UINT flags = ILC_COLOR32|ILC_MASK;

    /* must use this info, since image can be a driver image loaded from resources */
    iupdrvImageGetInfo(bmp, &width, &height, &bpp);

    /* create the image list if does not exist */
    image_list = ImageList_Create(width, height, flags, 0, 50);
    SendMessage(ih->handle, TCM_SETIMAGELIST, 0, (LPARAM)image_list);
  }
  else
    iupdrvImageGetInfo(bmp, NULL, NULL, &bpp);

  /* check if that bitmap is already added to the list,
     but we can not compare with the actual bitmap at the list since it is a copy */
  count = ImageList_GetImageCount(image_list);
  for (i=0; i<count; i++)
  {
    if (bmp_array_data[i] == bmp)
      return i;
  }

  if (bpp == 8)
  {
    Ihandle* image = IupGetHandle(name);
    if (image)
    {
      iupAttribSetStr(image, "_IUPIMG_NO_INVERT", "1");
      hMask = iupdrvImageCreateMask(image);
      iupAttribSetStr(image, "_IUPIMG_NO_INVERT", NULL);
    }
  }

  bmp_array_data = iupArrayInc(bmp_array);
  bmp_array_data[i] = bmp;
  ret = ImageList_Add(image_list, bmp, hMask);  /* the bmp is duplicated at the list */
  DeleteObject(hMask);
  return ret;
}