// call only once at the beginning of program
void RegisterSplitterWndClass() {
    if (splitterBmp)
        return;

    static WORD dotPatternBmp[8] = {
        0x00aa, 0x0055, 0x00aa, 0x0055, 0x00aa, 0x0055, 0x00aa, 0x0055
    };

    splitterBmp = CreateBitmap(8, 8, 1, 1, dotPatternBmp);
    splitterBrush = CreatePatternBrush(splitterBmp);

    WNDCLASSEX wcex;
    FillWndClassEx(wcex, SPLITTER_CLASS_NAME, WndProcSplitter);
    RegisterClassEx(&wcex);
}