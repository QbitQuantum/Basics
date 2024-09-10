void CBarBitmapWin32::DrawLetter(int left, int top,
                                 char ch)
{
    if (ch==' ')
        return;

    BMP eBmp;
    int topMargin;
    int width=0;

    if (ch>='A' && ch<='Z') {
        LoadFont(IDB_FONT_UPPER, eBmp);
        topMargin=(ch-'A')*13;

        switch (ch) {
        case 69:
            width=10;
            break;
        case 70:
            width=9;
            break;
        case 73:
            width=6;
            break;
        case 74:
            width=8;
            break;
        case 76:
            width=10;
            break;
        case 77:
            width=16;
            break;
        case 80:
            width=9;
            break;
        case 83:
            width=9;
            break;
        case 84:
            width=10;
            break;
        case 87:
            width=15;
            break;
        case 89:
            width=10;
            break;
        case 90:
            width=9;
            break;
        default:
            width=12;
        }
    }
    else if (ch>='a' && ch<='z') {
        LoadFont(IDB_FONT_LOWER, eBmp);
        topMargin=(ch-'a')*13;

        switch (ch) {
        case 102:
            width=5;
            break;
        case 105:
            width=4;
            break;
        case 106:
            width=4;
            break;
        case 107:
            width=9;
            break;
        case 108:
            width=4;
            break;
        case 109:
            width=12;
            break;
        case 114:
            width=6;
            break;
        case 115:
            width=7;
            break;
        case 116:
            width=5;
            break;
        case 119:
            width=10;
            break;
        case 122:
            width=6;
            break;
        default:
            width=8;
        }
    }
    else
        throw CBarBitmapException("Letter not supported");

    for (int i=0; i<width; i++)
        for (int j=0; j<13; j++)
            m_bmp->SetPixel(left+i,
                            top+j,
                            eBmp.GetPixel(i, topMargin+j));
}