static void DrawCallNotification(unsigned char const *pVal, int Len)
{
    PrintW("-DrwCall:");
    PrintQ(pVal, Len);

    Draw_t const *pItem = CallItem;
    Draw_t Info;
    unsigned char i = 0;

    ClearSram(NOTIF_MODE);
    // quit icon
    memcpy(&Info, pItem++, sizeof(Draw_t));
    Draw(&Info, NULL, NOTIF_MODE);

    // small phone icon
    memcpy(&Info, pItem++, sizeof(Draw_t));
    Draw(&Info, NULL, NOTIF_MODE);

    // timestamp icon
    memcpy(&Info, pItem++, sizeof(Draw_t));
    Draw(&Info, NULL, NOTIF_MODE);

    // timestamp
    memcpy(&Info, pItem++, sizeof(Draw_t));
    Draw(&Info, NULL, NOTIF_MODE);

    // call from
    memcpy(&Info, pItem++, sizeof(Draw_t));
    Info.Width = sizeof(Text) - 1;
    Draw(&Info, Text, NOTIF_MODE);

    // caller name
    memcpy(&Info, pItem, sizeof(Draw_t));

    if (*pVal >= '0' && *pVal <= '9' || *pVal == '+')
    {
        SetCallerNumber(pVal, Len);
        pVal = NoName;
        Len = sizeof(NoName) - 1;
    }

    // split and draw first, last names and call number if available
//  while (Len >= 0)
//  {
//    i = 0; while (pVal[i] != SPACE && i < Len) i++;
//
//    PrintF(" W:%u", i);
//    Info.Width = i;
//    Draw(&Info, pVal, NOTIF_MODE);
//
//    memcpy(&Info, pItem, sizeof(Draw_t));
//    Info.Y += CALLER_NAME_HEIGHT;
//    pVal += i + 1;
//    Len -= i + 1;
//  }

    i = 0;
    while (pVal[i] != SPACE && i < Len) i++;

    PrintF(" W:%u", i);
    Info.Width = i;
    Draw(&Info, pVal, NOTIF_MODE);

    if (i < Len - 1)
    {
        memcpy(&Info, pItem, sizeof(Draw_t));
        Info.Y += CALLER_NAME_HEIGHT;
        pVal += i + 1;
        Len -= i + 1;
        Info.Width = Len;
        Draw(&Info, pVal, NOTIF_MODE);
    }

    if (pCallerNumber)
    {
        memcpy(&Info, &CallItem[CALLER_NUMBER_ITEM], sizeof(Draw_t));
        Info.Width = NumberLen;
        Draw(&Info, pCallerNumber, NOTIF_MODE);

        vPortFree(pCallerNumber);
        pCallerNumber = NULL;
    }

    CreateAndSendMessage(ChangeModeMsg, NOTIF_MODE | MSG_OPT_UPD_INTERNAL);
}