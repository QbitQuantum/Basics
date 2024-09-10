HRESULT CLangBarItemButton::_GetIcon(HICON *phIcon, BOOL bNT62)
{
    size_t iconindex = 0;
    WORD iconid = 0;

    if(!_pTextService->_IsKeyboardDisabled() && _pTextService->_IsKeyboardOpen())
    {
        switch(_pTextService->inputmode)
        {
        case im_hiragana:
            iconindex = 1;
            break;
        case im_katakana:
            iconindex = 2;
            break;
        case im_katakana_ank:
            iconindex = 3;
            break;
        case im_jlatin:
            iconindex = 4;
            break;
        case im_ascii:
            iconindex = 5;
            break;
        default:
            break;
        }
    }

    if(bNT62)
    {
        if(iconindex < _countof(iconIDZ))
        {
            iconid = iconIDZ[iconindex];
        }
    }
    else
    {
        if(iconindex < _countof(iconIDX))
        {
            iconid = iconIDX[iconindex];
        }
    }

    //DPIを考慮
    HDC hdc = GetDC(nullptr);
    int dpi = GetDeviceCaps(hdc, LOGPIXELSY);
    ReleaseDC(nullptr, hdc);
    int size = MulDiv(16, dpi, 96);

    *phIcon = (HICON)LoadImageW(g_hInst, MAKEINTRESOURCEW(iconid), IMAGE_ICON, size, size, LR_SHARED);

    return (*phIcon != nullptr) ? S_OK : E_FAIL;
}