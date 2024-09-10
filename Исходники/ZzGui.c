RT_H RT_CALL ZzCreateLeftTab(RT_GUI_RECT* lpPosition, RT_H hMainWindow, RT_H hInstance, RT_H hFont)
{
  TC_ITEM rtItem;
  RT_H hResult;

  hResult = CreateWindowEx(0,                                         /* ExStyle. */
                           WC_TABCONTROL,                             /* Tab class name. */
                           _R("LeftTab"),                             /* Window name. */
                           WS_VISIBLE | WS_CHILD |                    /* Style. */
                           TCS_FIXEDWIDTH,
                           lpPosition->nX, lpPosition->nY,            /* Position. */
                           lpPosition->nWidth, lpPosition->nHeight,   /* Size. */
                           hMainWindow,                               /* Parent Window. */
                           (HMENU)ZZ_RESOURCES_LEFT_TAB_CTRL_ID,      /* Control id. */
                           hInstance,                                 /* Application instance. */
                           RT_NULL);

  if (!hResult) goto handle_error;

  /* Cannot check errors. */
  TabCtrl_SetItemSize(hResult, 60, ZZ_GUI_TAB_HEIGHT);
  /* Cannot check errors. */
  SendMessage(hResult, WM_SETFONT, (WPARAM)hFont, TRUE);

  rtItem.mask = TCIF_TEXT | TCIF_PARAM;

  rtItem.pszText = ZzGetString(ZZ_STRINGS_CLIMBERS);
  rtItem.lParam = ZZ_RESOURCES_CLIMBERS;
  if (SendMessage(hResult, TCM_INSERTITEM, 1, (LPARAM)&rtItem) == -1) goto handle_error;

  rtItem.pszText = ZzGetString(ZZ_STRINGS_ROUTES);
  rtItem.lParam = ZZ_RESOURCES_ROUTES;
  if (SendMessage(hResult, TCM_INSERTITEM, 2, (LPARAM)&rtItem) == -1) goto handle_error;

  rtItem.pszText = ZzGetString(ZZ_STRINGS_GRADES);
  rtItem.lParam = ZZ_RESOURCES_GRADES;
  if (SendMessage(hResult, TCM_INSERTITEM, 3, (LPARAM)&rtItem) == -1) goto handle_error;



  if (!SetWindowSubclass(hResult, &ZzLeftTabSubclassProc, 0, 0)) goto handle_error;

free_resources:
  return hResult;

handle_error:
  if (hResult)
  {
    DestroyWindow(hResult);
    hResult = RT_NULL;
  }
  goto free_resources;
}