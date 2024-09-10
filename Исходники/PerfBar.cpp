void CPerfBar::PaintData(HDC hdc, POINT offset)
{
    Configuration::pages_t& pages = m_config.GetPages();
    //Configuration::counters_t & counters = m_config.GetCounters();

    if (pages.empty()) {
        return;
    }

    if (pages.size() <= m_currentPage) {
        m_currentPage = pages.size() - 1;
    }

    Configuration::Page& page = pages[m_currentPage];

    if (page.Lines.empty()) {
        return;
    }

    auto values = m_perfMonitor.GetValues();

    TEXTMETRIC textMetric;
    GetTextMetrics(hdc, &textMetric);

    wchar_t buf[1024] = { 0 };
    wchar_t display[1024] = { 0 };

    for (size_t i = 0; i < page.Lines.size(); ++i) {
        buf[0] = 0;

        Configuration::Line& line = page.Lines[i];

        for (auto iit = line.Display.begin(); iit != line.Display.end(); ++iit) {
            auto value_it = values.find(iit->Counter);

            wchar_t formattedValue[256] = { 0 };
            if (value_it == values.end()) {
                wcscpy_s(formattedValue, _countof(formattedValue), L"[N/A]");
            } else {
                double val = value_it->second;
                if (iit->Divide > 0) {
                    val /= iit->Divide;
                }

                wchar_t formattingString[256] = { 0 };
                swprintf_s(
                    formattingString,
                    _countof(formattingString),
                    L"%s%d%s",
                    L"%.",
                    iit->Decimals > 0 ? iit->Decimals : 0,
                    L"f"
                );

                swprintf_s(
                    formattedValue,
                    _countof(formattedValue),
                    formattingString,
                    val
                );
            }

            swprintf_s(
                display,
                _countof(display),
                L"%s%s%s",
                iit->Prefix.c_str(),
                formattedValue,
                iit->Suffix.c_str()
            );

            wcscat_s(buf, _countof(buf), display);
        }

        RECT rc;
        GetClientRect(&rc);

        int offsetY = page.OffsetY + ((int)i * (textMetric.tmHeight - textMetric.tmExternalLeading));

        rc.top += offsetY + offset.y;
        rc.bottom += offset.y;
        rc.left += offset.x;
        rc.right += offset.x;

        HFONT font =
            CreateFontW(
                -MulDiv((int)line.Font.Size, GetDeviceCaps(hdc, LOGPIXELSY), 72),
                0,
                0,
                0,
                line.Font.Bold ? FW_BOLD : 0,
                line.Font.Italic,
                FALSE,
                FALSE,
                ANSI_CHARSET,
                0,
                0,
                0,
                0,
                line.Font.Family.c_str()
            );

        SetTextColor(hdc, line.Font.Color);
        HFONT oldFont = (HFONT)SelectObject(hdc, font);
        DrawTextW(hdc, buf, (int)wcslen(buf), &rc, DT_LEFT | DT_TOP);
        SelectObject(hdc, oldFont);
        DeleteObject(font);
    }
}