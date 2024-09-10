HFONT CachedFont::GetHFont() {
    if (!hFont) {
        LOGFONTW lf;
        // TODO: Graphics is probably only used for metrics,
        // so this might not be 100% correct (e.g. 2 monitors with different DPIs?)
        // but previous code wasn't much better
        Graphics *gfx = AllocGraphicsForMeasureText();
        Status status = font->GetLogFontW(gfx, &lf);
        FreeGraphicsForMeasureText(gfx);
        CrashIf(status != Ok);
        hFont = CreateFontIndirectW(&lf);
        CrashIf(!hFont);
    }
    return hFont;
}