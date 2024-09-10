RT_B RT_API RtCreateGuiCommandMenuItemManager(RT_GUI_COMMAND_MENU_ITEM_MANAGER* lpGuiCommandMenuItemManager, RT_GUI_COMMAND_MENU_ITEM* lpCommandMenuItems, RT_UN unCommandMenuItemsCount, RT_H hInstance)
{
  RT_H hDc;
  RT_N nIconsCount;
  RT_N nImageIndex;
  RT_H hTemporaryToolBar;
  RT_N nSystemImageList;
  RT_N lpSystemImageListIndex[3];
  RT_UN32 unOsVersion;
  RT_UN32 lpMaskBuffer[256];
  RT_UN32 lpColorBuffer[256];
  RT_N nI;
  RT_B bResult;

  /* Used to load system images. */
  hTemporaryToolBar = RT_NULL;

  hDc = RT_NULL;

  unOsVersion = RtGetOsVersion(RT_NULL);

  lpGuiCommandMenuItemManager->lpCommandMenuItems = lpCommandMenuItems;
  lpGuiCommandMenuItemManager->nCommandMenuItemsCount = unCommandMenuItemsCount;

  /* Count icons. The result is not accurate as the user can use system image lists, but it will help for initial image list size. */
  nIconsCount = 0;
  for (nI = 0; nI < unCommandMenuItemsCount; nI++)
  {
    if (lpCommandMenuItems[nI].hIcon)
    {
      nIconsCount++;
    }
    lpCommandMenuItems[nI].hBitmap = RT_NULL;
  }

  lpGuiCommandMenuItemManager->hToolBarImageList = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, nIconsCount, 8);
  if (!lpGuiCommandMenuItemManager->hToolBarImageList) goto handle_error;

  /* By default, there is no system image list loaded. */
  for (nI = 0; nI < 3; nI++)
  {
    lpSystemImageListIndex[nI] = -1;
  }

  /* Loop on command menu items. */
  nImageIndex = 0;
  for (nI = 0; nI < unCommandMenuItemsCount; nI++)
  {
    if (lpCommandMenuItems[nI].hIcon)
    {
      /* The user has provided an icon. */
      if (ImageList_AddIcon(lpGuiCommandMenuItemManager->hToolBarImageList, lpCommandMenuItems[nI].hIcon) == -1)
      {
        goto handle_error;
      }
      lpCommandMenuItems[nI].unImageIndex = nImageIndex;
      nImageIndex++;
    }
    else if (lpCommandMenuItems[nI].nSystemImageList != -1)
    {
      /* The user want to use an icon from a system image list. */
      switch (lpCommandMenuItems[nI].nSystemImageList)
      {
        case IDB_STD_SMALL_COLOR:
          nSystemImageList = 0;
          break;
        case IDB_VIEW_SMALL_COLOR:
          nSystemImageList = 1;
          break;
        case IDB_HIST_SMALL_COLOR:
          nSystemImageList = 2;
          break;
        default:
          nSystemImageList = -1;
      }
      if (nSystemImageList == -1)
      {
        RtSetLastError(RT_ERROR_BAD_ARGUMENTS);
        goto handle_error;
      }
      /* If the system list is not already loaded in the  image list. */
      if (lpSystemImageListIndex[nSystemImageList] == -1)
      {
        /* We need a temporary toolbar to load system images in the image list. */
        if (!hTemporaryToolBar)
        {
          hTemporaryToolBar = CreateWindowEx(0,       /* Extended style. */
                          TOOLBARCLASSNAME,           /* Class name. */
                          _R("TemporaryToolBar"),     /* Window name. */
                          0,                          /* Style. */
                          0, 0, 0, 0,
                          RT_NULL,                     /* Parent. */
                          RT_NULL,                     /* Control id. */
                          hInstance,
                          RT_NULL);
          if (!hTemporaryToolBar)
          {
            goto handle_error;
          }
          /* We use our main image list as temporary image list. */
          SendMessage(hTemporaryToolBar, TB_SETIMAGELIST, 0, (LPARAM)lpGuiCommandMenuItemManager->hToolBarImageList);
        }
        SendMessage(hTemporaryToolBar, TB_LOADIMAGES, (WPARAM)lpCommandMenuItems[nI].nSystemImageList, (LPARAM)HINST_COMMCTRL);
        lpSystemImageListIndex[nSystemImageList] = nImageIndex;
        nImageIndex = ImageList_GetImageCount(lpGuiCommandMenuItemManager->hToolBarImageList);
      }
      lpCommandMenuItems[nI].unImageIndex = lpSystemImageListIndex[nSystemImageList] + lpCommandMenuItems[nI].nSystemImageIndex;

      /* Create the menu icon from the image list. */
      lpCommandMenuItems[nI].hIcon = ImageList_ExtractIcon(0, lpGuiCommandMenuItemManager->hToolBarImageList, lpCommandMenuItems[nI].unImageIndex);
      if (!lpCommandMenuItems[nI].hIcon)
      {
        goto handle_error;
      }
    }
    else
    {
      lpCommandMenuItems[nI].unImageIndex = -1;
    }

    /* Under vista, we must use a PARGB bitmap for menus. */
    if (unOsVersion >= 6)
    {
      if (lpCommandMenuItems[nI].hIcon)
      {
        /* Get a reference DC. */
        if (!hDc)
        {
          hDc = GetDC(RT_NULL);
          if (!hDc) goto handle_error;
        }
        /* Create a PARG bitmap from the icon. */
        lpCommandMenuItems[nI].hBitmap = RtConvertIconToPargbBitmap(lpCommandMenuItems[nI].hIcon, 16, 16, lpMaskBuffer, lpColorBuffer, hDc);
        if (!lpCommandMenuItems[nI].hBitmap) goto handle_error;
      }
    }
  }

  bResult = RT_TRUE;
  goto free_resources;
handle_error:
  /* Free allocated content in case of error. */
  if (lpGuiCommandMenuItemManager->hToolBarImageList)
  {
    ImageList_Destroy(lpGuiCommandMenuItemManager->hToolBarImageList);
  }
  /* Free allocated icons and bitmaps. */
  for (nI = 0; nI < unCommandMenuItemsCount; nI++)
  {
    if (lpCommandMenuItems[nI].nSystemImageIndex != -1)
    {
      if (lpCommandMenuItems[nI].hIcon)
      {
        DestroyIcon(lpCommandMenuItems[nI].hIcon);
      }
    }
    if (lpCommandMenuItems[nI].hBitmap)
    {
      DeleteObject(lpCommandMenuItems[nI].hBitmap);
    }
  }
  bResult = RT_FALSE;
free_resources:
  if (hDc)
  {
    if (!ReleaseDC(RT_NULL, hDc) && bResult)
    {
      hDc = RT_NULL;
      goto handle_error;
    }
    hDc = RT_NULL;
  }
  if (hTemporaryToolBar)
  {
    if (!DestroyWindow(hTemporaryToolBar) && bResult)
    {
      hTemporaryToolBar = RT_NULL;
      goto handle_error;
    }
    hTemporaryToolBar = RT_NULL;
  }

  return bResult;
}