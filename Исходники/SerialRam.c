void SetWidgetList(tMessage *pMsg)
{
  static Widget_t *pCurrWidget = NULL; // point to Widget in current Widget[]
  static Widget_t *pNextWidget = NULL; // point to Widget in new Widget[]
  static unsigned char ChangedClockWidget = INVALID_ID;

  xSemaphoreTake(SramMutex, portMAX_DELAY);

  WidgetList_t *pMsgWgtLst = (WidgetList_t *)pMsg->pBuffer;
  unsigned char WidgetNum = pMsg->Length / WIDGET_HEADER_LEN;

  unsigned char i = 0;
  PrintF(">SetWLst I:%d %s %d %s %d", WGTLST_INDEX(pMsg->Options), "T:", WGTLST_TOTAL(pMsg->Options), "Num:", WidgetNum);
  for(; i<WidgetNum; ++i) {PrintH(pMsgWgtLst[i].Id); PrintH(pMsgWgtLst[i].Layout);} PrintR();

  if (pNextWidget == NULL) // first time call, only add widgets
  {
    pCurrWidget = pCurrWidgetList;
    pNextWidget = &Widget[0];
  }
  else
  {
    if (WGTLST_INDEX(pMsg->Options) == 0 &&
      (pCurrWidget != pCurrWidgetList || (pNextWidget != &Widget[0] && pNextWidget != &Widget[MAX_WIDGET_NUM])))
    { // last SetWLst failed in the middle.Clean up whole list
      PrintS("# Last SetWgtLst broken!");

      pCurrWidget = pCurrWidgetList;
      pNextWidget = &Widget[0] + (&Widget[MAX_WIDGET_NUM] - pCurrWidgetList);
    }
  }

  while (WidgetNum) // number of list items
  {
      /* old clock widgets */
    if (!IS_CLOCK_WIDGET(pMsgWgtLst->Layout) && pMsgWgtLst->Id <= CLOCK_WIDGET_ID_RANGE) TestFaceId(pMsgWgtLst);
    unsigned char Change = GetWidgetChange(pCurrWidget->Id, pCurrWidget->Layout, pMsgWgtLst->Id, pMsgWgtLst->Layout);
    
    switch (Change)
    {
    case WGT_CHG_CLK_FACE:
      PrintS("Chg ClkFce");
      if (ON_CURRENT_PAGE(pMsgWgtLst->Layout)) ChangedClockWidget = pMsgWgtLst->Id;
      
    case WGT_CHG_SETTING:
     //cpy layout to curr; cpy curr to next; msg, curr, next ++
      PrintF("=%02X", pCurrWidget->Id);
      pCurrWidget->Id = pMsgWgtLst->Id;
      pCurrWidget->Layout = pMsgWgtLst->Layout;
      *pNextWidget++ = *pCurrWidget++;
      pMsgWgtLst ++;
      WidgetNum --;
      break;

    case WGT_CHG_CLK_ADD:
      PrintS("+Clk");
      if (ON_CURRENT_PAGE(pMsgWgtLst->Layout)) ChangedClockWidget = pMsgWgtLst->Id;

    case WGT_CHG_ADD: //pCurrWidget->Id > pMsgWgtLst->Id)
     // add new widget: cpy msg to next; msg and next ++; curr stays
      PrintF("+%02X", pMsgWgtLst->Id);

      pNextWidget->Id = pMsgWgtLst->Id;
      pNextWidget->Layout = pMsgWgtLst->Layout;
      AssignWidgetBuffer(pNextWidget);

      pNextWidget ++;
      pMsgWgtLst ++;
      WidgetNum --;
      break;
      
    case WGT_CHG_REMOVE:
    // remove widget: curr ++
      PrintF("-%02X", pCurrWidget->Id);
      FreeWidgetBuffer(pCurrWidget);
      pCurrWidget ++;
      break;
      
    default: break;
    }
  }
  PrintR();

  // if part index + 1 == parts, SetWidgetList complete
  if (WGTLST_TOTAL(pMsg->Options) == WGTLST_INDEX(pMsg->Options) + 1)
  {
//    PrintS("C:");
//    for (i=0; pCurrWidgetList[i].Id != INVALID_ID && i < MAX_WIDGET_NUM; ++i) PrintH(pCurrWidgetList[i].Id);
//    PrintR();

    while (pCurrWidget->Id != INVALID_ID && pCurrWidget < &pCurrWidgetList[MAX_WIDGET_NUM])
    {
      FreeWidgetBuffer(pCurrWidget);
      pCurrWidget->Id = INVALID_ID;
      pCurrWidget ++;
    }

    for (i = 0; i < MAX_WIDGET_NUM; ++i)
    {
      if (pCurrWidgetList[i].Id != INVALID_ID)
      { // clear the widget id in the curr list
        pCurrWidgetList[i].Id = INVALID_ID;
      }
    }

    pNextWidget = pCurrWidgetList;
    pCurrWidgetList = &Widget[0] + (&Widget[MAX_WIDGET_NUM] - pCurrWidgetList);
    pCurrWidget = pCurrWidgetList;

//    PrintS("N:");
//    for (i=0; pCurrWidgetList[i].Id != INVALID_ID; ++i) PrintH(pCurrWidgetList[i].Id);
//    PrintR();
    PrintF("Tg:%04X", BufTag);

    if (ChangedClockWidget != INVALID_ID)
    {
      CreateAndSendMessage(DrawClockWidgetMsg, ChangedClockWidget);
      ChangedClockWidget = INVALID_ID;
    }
  }
  xSemaphoreGive(SramMutex);
}