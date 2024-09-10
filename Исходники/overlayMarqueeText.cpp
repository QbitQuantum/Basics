//
//	Draw overlay
//
PLUGIN_EXPORT void PluginUpdateOverlay()
{

    if (!pRenderHelper)
        return;

    // lock overlay image
    auto pLock = pRenderHelper->BeginFrame();
    if (!pLock)
        return;

    int w = pLock->dwWidth;
    int h = pLock->dwHeight;

    Gdiplus::Graphics *pGraphics = pRenderHelper->GetGraphics();

    //-----------------------------------------
    // draw Text Overlay

    // set options
    pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

    // clear back
    pGraphics->Clear(Gdiplus::Color(0, 0, 0, 0));
    WCHAR s[128];
    _itow_s(PC_GetConfirmedProcessID(), s, 10);

    if (PathFileExists(pFileName)) {
        string textContents = "";
        WIN32_FILE_ATTRIBUTE_DATA       attribs;
        GetFileAttributesExW(pFileName, GetFileExInfoStandard, &attribs);

        FILETIME modifyTime = attribs.ftLastWriteTime;
        if (CompareFileTime(&modifyTime, &oldModifyTime) > 0) {
            oldModifyTime = modifyTime;
            string line;
            ifstream myfile;
            myfile.open(pFileName);
            if (myfile.is_open())
            {
                while (getline(myfile, line))
                {
                    textContents += line;
                }
                myfile.close();
            }
            textLength = textContents.length();
            wcTextContents[textLength] = 0;
            std::copy(textContents.begin(), textContents.end(), wcTextContents);
        }
    }
    // draw back if required
    if (bShowBackground)
    {
        Gdiplus::RectF bound;
        pRenderHelper->GetTextExtent(wcTextContents, pFont, &bound);
        pGraphics->FillRectangle(pBackBrush, bound);
    }

    // draw text

    Gdiplus::RectF bound;
    pRenderHelper->GetTextExtent(wcTextContents, pFont, &bound);

    if (bound.Width > w) {
        wchar_t wcNewTextContents[256];
        wcNewTextContents[textLength * 2 + 5] = 0;
        swprintf_s(wcNewTextContents, L"%s     %s", wcTextContents, wcTextContents);
        Gdiplus::RectF newbound;
        pRenderHelper->GetTextExtent(wcNewTextContents, pFont, &newbound);
        pRenderHelper->DrawString(wcNewTextContents, pFont, Gdiplus::Point(0 - scroll, 0), pTextBrush, pBackBrush);
        scroll += 2;
        if (scroll > newbound.Width - bound.Width)
            scroll = 0;
    }
    else {
        pRenderHelper->DrawString(wcTextContents, pFont, Gdiplus::Point(0, 0), pTextBrush, pBackBrush);
    }
    // fill overlay image
    pRenderHelper->EndFrame();

}