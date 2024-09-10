void DxSprite::DrawString(int X, int Y, const std::wstring & text, int R, int G, int B, int A, DxFont & F)
{
    float blendFactor[4] = { 1.0f };
    GetDX11Context()->OMSetBlendState(TransparentBS, blendFactor, 0xFFFFFFFF);

    BeginBatch(F.GetFontSheetSRV());

    UINT length = text.length();

    int posX = X;
    int posY = Y;

    XMCOLOR color;
    XMVECTOR Vec = XMVectorSet( R ? (float)( R / 255.0f ) : 0.0f, G ? (float)( G / 255.0f ) : 0.0f, B ? (float)( B / 255.0f ) : 0.0f, A ? (float)( A / 255.0f ) : 0.0f );
    XMStoreColor(&color, Vec);

    for(UINT i = 0; i < length; ++i)
    {
        WCHAR character = text[i];

        if(character == ' ') 
            posX += F.GetSpaceWidth();
        else if(character == '\n')
        {
            posX = X;
            posY += F.GetCharHeight();
        }
        else
        {
            const CD3D11_RECT & charRect = F.GetCharRect(character);

            int width  = charRect.right - charRect.left;
            int height = charRect.bottom - charRect.top;

            Draw(CD3D11_RECT(posX, posY, posX + width, posY + height), charRect, color);

            posX += width + 1;
        }
    }

    EndBatch();

    GetDX11Context()->OMSetBlendState(0, blendFactor, 0xFFFFFFFF);
}