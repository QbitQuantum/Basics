HRESULT OnRender(HDC hdc, const RECT &rcPaint)
{
    WCHAR wzText[512];

    FillRect(hdc, &rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));

    StringCchCopyW(wzText, ARRAYSIZE(wzText), L"Source: ");

    switch(g_inputSource.deviceType)
    {
        case IMDT_UNAVAILABLE:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Unavailable\n");
            break;

        case IMDT_KEYBOARD:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Keyboard\n");
            break;

        case IMDT_MOUSE:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Mouse\n");
            break;

        case IMDT_TOUCH:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Touch\n");
            break;

        case IMDT_PEN:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Pen\n");
            break;

    }

    StringCchCatW(wzText, ARRAYSIZE(wzText), L"Origin: ");

    switch(g_inputSource.originId)
    {
        case IMO_UNAVAILABLE:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Unavailable\n");
            break;

        case IMO_HARDWARE:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Hardware\n");
            break;

        case IMO_INJECTED:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"Injected\n");
            break;

        case IMO_SYSTEM:
            StringCchCatW(wzText, ARRAYSIZE(wzText), L"System\n");
            break;
    }

    DrawText(hdc, wzText, (int)wcslen(wzText), (LPRECT)&rcPaint, DT_TOP | DT_LEFT);

    return S_OK;
}