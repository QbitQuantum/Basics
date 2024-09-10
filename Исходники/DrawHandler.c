void DrawMsgHandler(tMessage *pMsg)
{
  static Draw_t *pInfo;
  static unsigned char *pData;
  static unsigned int Size = 0;

  if (pMsg->Options & DRAW_MSG_BEGIN)
  {
    pInfo = (Draw_t *)pMsg->pBuffer;
    pData = pMsg->pBuffer + DRAW_INFO_SIZE;

    if (!(pMsg->Options & DRAW_MSG_END))
    {
      pInfo = (Draw_t *)pvPortMalloc(DRAW_INFO_SIZE);
      PrintF("%cA:%04X %u", pInfo ? PLUS : NOK, pInfo, DRAW_INFO_SIZE);
      if (pInfo == NULL) return;

      memcpy(pInfo, pMsg->pBuffer, DRAW_INFO_SIZE);
      PrintF("Id:%02X X:%u Y:%u Opt:%02X", pInfo->Id, pInfo->X, pInfo->Y, pInfo->Opt);
      PrintF("W:%u H:%u WgtId:%02X", pInfo->Width, pInfo->Height, pInfo->WidgetId);
      PrintF("TxtLen:%u Align:%u", pInfo->TextLen, pInfo->Align);

      if (pInfo->Id & DRAW_ID_TYPE_BMP)
        Size = pInfo->Opt & DRAW_OPT_FILL ? 1 : WIDTH_IN_BYTES(pInfo->Width) * pInfo->Height;
      else Size = pInfo->TextLen;

      pData = (unsigned char *)pvPortMalloc(Size);
      PrintF("%cA:%04X %u", pData ? PLUS : NOK, pData, Size);
      if (pData == NULL)
      {
        vPortFree(pInfo);
        return;
      }

      Size = pMsg->Length - DRAW_INFO_SIZE;
      memcpy(pData, pMsg->pBuffer + DRAW_INFO_SIZE, Size);
    }
  }
  else // pure data in payload
  {
    if (pData == NULL)
    {
      PrintS("#DrwMsg:empty payload");
      return;
    }
    memcpy(pData + Size, pMsg->pBuffer, pMsg->Length);
    Size += pMsg->Length;
  }

  if (pMsg->Options & DRAW_MSG_END)
  {
    unsigned char Mode = (pMsg->Options & DRAW_MSG_MODE) >> 6;
    if (Mode == IDLE_MODE) CreateDrawBuffer(pInfo->WidgetId);

    Draw(pInfo, pData, Mode);

    if (Mode == IDLE_MODE && (pMsg->Options & DRAW_WIDGET_END))
      DrawWidgetToSram(pInfo->WidgetId);

    if (Size)
    {
      PrintF("-F:%04X %04X", pInfo, pData);
      vPortFree(pData);
      vPortFree(pInfo);
      Size = 0;
    }
  }