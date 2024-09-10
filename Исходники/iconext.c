VOID EtpNetworkIconUpdateCallback(
    _In_ struct _PH_NF_ICON *Icon,
    _Out_ PVOID *NewIconOrBitmap,
    _Out_ PULONG Flags,
    _Out_ PPH_STRING *NewText,
    _In_opt_ PVOID Context
    )
{
    static PH_GRAPH_DRAW_INFO drawInfo =
    {
        16,
        16,
        PH_GRAPH_USE_LINE_2,
        2,
        RGB(0x00, 0x00, 0x00),

        16,
        NULL,
        NULL,
        0,
        0,
        0,
        0
    };
    ULONG maxDataCount;
    ULONG lineDataCount;
    PFLOAT lineData1;
    PFLOAT lineData2;
    FLOAT max;
    ULONG i;
    HBITMAP bitmap;
    PVOID bits;
    HDC hdc;
    HBITMAP oldBitmap;
    HANDLE maxNetworkProcessId;
    PPH_PROCESS_ITEM maxNetworkProcessItem;
    PH_FORMAT format[6];

    // Icon

    Icon->Pointers->BeginBitmap(&drawInfo.Width, &drawInfo.Height, &bitmap, &bits, &hdc, &oldBitmap);
    maxDataCount = drawInfo.Width / 2 + 1;
    lineData1 = _alloca(maxDataCount * sizeof(FLOAT));
    lineData2 = _alloca(maxDataCount * sizeof(FLOAT));

    lineDataCount = min(maxDataCount, EtNetworkReceiveHistory.Count);
    max = 1024 * 1024; // minimum scaling of 1 MB.

    for (i = 0; i < lineDataCount; i++)
    {
        lineData1[i] = (FLOAT)PhGetItemCircularBuffer_ULONG(&EtNetworkReceiveHistory, i);
        lineData2[i] = (FLOAT)PhGetItemCircularBuffer_ULONG(&EtNetworkSendHistory, i);

        if (max < lineData1[i] + lineData2[i])
            max = lineData1[i] + lineData2[i];
    }

    PhDivideSinglesBySingle(lineData1, max, lineDataCount);
    PhDivideSinglesBySingle(lineData2, max, lineDataCount);

    drawInfo.LineDataCount = lineDataCount;
    drawInfo.LineData1 = lineData1;
    drawInfo.LineData2 = lineData2;
    drawInfo.LineColor1 = PhGetIntegerSetting(L"ColorIoReadOther");
    drawInfo.LineColor2 = PhGetIntegerSetting(L"ColorIoWrite");
    drawInfo.LineBackColor1 = PhHalveColorBrightness(drawInfo.LineColor1);
    drawInfo.LineBackColor2 = PhHalveColorBrightness(drawInfo.LineColor2);

    if (bits)
        PhDrawGraphDirect(hdc, bits, &drawInfo);

    SelectObject(hdc, oldBitmap);
    *NewIconOrBitmap = bitmap;
    *Flags = PH_NF_UPDATE_IS_BITMAP;

    // Text

    if (EtMaxNetworkHistory.Count != 0)
        maxNetworkProcessId = UlongToHandle(PhGetItemCircularBuffer_ULONG(&EtMaxNetworkHistory, 0));
    else
        maxNetworkProcessId = NULL;

    if (maxNetworkProcessId)
        maxNetworkProcessItem = PhReferenceProcessItem(maxNetworkProcessId);
    else
        maxNetworkProcessItem = NULL;

    PhInitFormatS(&format[0], L"Network\nR: ");
    PhInitFormatSize(&format[1], EtNetworkReceiveDelta.Delta);
    PhInitFormatS(&format[2], L"\nS: ");
    PhInitFormatSize(&format[3], EtNetworkSendDelta.Delta);

    if (maxNetworkProcessItem)
    {
        PhInitFormatC(&format[4], '\n');
        PhInitFormatSR(&format[5], maxNetworkProcessItem->ProcessName->sr);
    }

    *NewText = PhFormat(format, maxNetworkProcessItem ? 6 : 4, 128);
    if (maxNetworkProcessItem) PhDereferenceObject(maxNetworkProcessItem);
}