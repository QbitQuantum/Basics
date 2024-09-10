void OBS::DrawStatusBar(DRAWITEMSTRUCT &dis)
{
    if(!App->bRunning)
        return;

    HDC hdcTemp = CreateCompatibleDC(dis.hDC);
    HBITMAP hbmpTemp = CreateCompatibleBitmap(dis.hDC, dis.rcItem.right-dis.rcItem.left, dis.rcItem.bottom-dis.rcItem.top);
    SelectObject(hdcTemp, hbmpTemp);

    SelectObject(hdcTemp, GetCurrentObject(dis.hDC, OBJ_FONT));

    //HBRUSH  hColorBrush = CreateSolidBrush((green<<8)|red);

    RECT rc;
    mcpy(&rc, &dis.rcItem, sizeof(rc));

    rc.left   -= dis.rcItem.left;
    rc.right  -= dis.rcItem.left;
    rc.top    -= dis.rcItem.top;
    rc.bottom -= dis.rcItem.top;

    FillRect(hdcTemp, &rc, (HBRUSH)(COLOR_BTNFACE+1));

    //DeleteObject(hColorBrush);

    //--------------------------------

    if(dis.itemID == 4)
    {
        DWORD green = 0xFF, red = 0xFF;

        statusBarData.bytesPerSec = App->bytesPerSec;
        statusBarData.strain = App->curStrain;
        //statusBarData.strain = rand()%101;

        if(statusBarData.strain > 50.0)
            green = DWORD(((50.0-(statusBarData.strain-50.0))/50.0)*255.0);

        double redStrain = statusBarData.strain/50.0;
        if(redStrain > 1.0)
            redStrain = 1.0;

        red = DWORD(redStrain*255.0);

        //--------------------------------

        HBRUSH  hColorBrush = CreateSolidBrush((green<<8)|red);

        RECT rcBox = {0, 0, 20, 20};
        /*rc.left += dis.rcItem.left;
        rc.right += dis.rcItem.left;
        rc.top += dis.rcItem.top;
        rc.bottom += dis.rcItem.top;*/
        FillRect(hdcTemp, &rcBox, hColorBrush);

        DeleteObject(hColorBrush);

        //--------------------------------

        SetBkMode(hdcTemp, TRANSPARENT);

        rc.left += 22;

        String strKBPS;
        strKBPS << IntString((statusBarData.bytesPerSec*8) / 1000) << TEXT("kb/s");
        //strKBPS << IntString(rand()) << TEXT("kb/s");
        DrawText(hdcTemp, strKBPS, strKBPS.Length(), &rc, DT_VCENTER|DT_SINGLELINE|DT_LEFT);
    }
    else
    {
        String strOutString;

        switch(dis.itemID)
        {
            case 0: strOutString << App->GetMostImportantInfo(); break;
            case 1:
                {
                    DWORD streamTimeSecondsTotal = App->totalStreamTime/1000;
                    DWORD streamTimeMinutesTotal = streamTimeSecondsTotal/60;
                    DWORD streamTimeSeconds = streamTimeSecondsTotal%60;

                    DWORD streamTimeHours = streamTimeMinutesTotal/60;
                    DWORD streamTimeMinutes = streamTimeMinutesTotal%60;

                    strOutString = FormattedString(TEXT("%u:%02u:%02u"), streamTimeHours, streamTimeMinutes, streamTimeSeconds);
                }
                break;
            case 2:
                {
                    double percentageDropped = 0.0;
                    if (OSTryEnterMutex(App->hStartupShutdownMutex))
                    {
                        if(App->network)
                        {
                            UINT numTotalFrames = App->network->NumTotalVideoFrames();
                            if(numTotalFrames)
                                percentageDropped = (double(App->network->NumDroppedFrames())/double(numTotalFrames))*100.0;
                        }
                        OSLeaveMutex(App->hStartupShutdownMutex);
                    }
                    strOutString << Str("MainWindow.DroppedFrames") << FormattedString(TEXT(" %u (%0.2f%%)"), App->curFramesDropped, percentageDropped);
                }
                break;
            case 3: strOutString << TEXT("FPS: ") << IntString(App->captureFPS); break;
        }

        if(strOutString.IsValid())
        {
            SetBkMode(hdcTemp, TRANSPARENT);
            DrawText(hdcTemp, strOutString, strOutString.Length(), &rc, DT_VCENTER|DT_SINGLELINE|DT_LEFT);
        }
    }

    //--------------------------------

    BitBlt(dis.hDC, dis.rcItem.left, dis.rcItem.top, dis.rcItem.right-dis.rcItem.left, dis.rcItem.bottom-dis.rcItem.top, hdcTemp, 0, 0, SRCCOPY);

    DeleteObject(hdcTemp);
    DeleteObject(hbmpTemp);
}