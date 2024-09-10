// クリップボードからビットマップを取得する関数
void SampleClipboard()
{
    if(!::IsClipboardFormatAvailable(CF_BITMAP))
    {
        return;
    }

    if(!::OpenClipboard(NULL))
    {
        return;
    }

    CImage image;
    HBITMAP hBitmap = (HBITMAP)::GetClipboardData(CF_BITMAP);
    if(hBitmap == NULL)
    {
        ::CloseClipboard();
        return;
    }

    CImage clip;

    // 
    clip.Attach(hBitmap);

    // イメージを保持しているデバイス コンテキストを取得
    HDC hdc = clip.GetDC();

    setTextColor(hdc, RGB(255, 0, 0));
    RECT rec;
    rec.top = 50;
    rec.left = 10;
    rec.right = 290;
    rec.bottom = 100;
    DrawText(hdc, "2019/04/12 XX:XX:XX", -1, &rec, NULL);

    clip.Detach();
    clip.ReleaseDC();

    ::CloseClipboard();

    // そのままファイルに保存することも可能
    // clip.Save(L"sample.png");
}