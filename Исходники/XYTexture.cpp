XYTexture::XYTexture(LPWSTR lpFileName)
{
    hbitmap=(HBITMAP)LoadImage(0,lpFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    BITMAP bitmap;
    GetObject(hbitmap,sizeof(BITMAP),&bitmap);
    bheight=bitmap.bmHeight;
    bwidth=bitmap.bmWidth;
    bit=bitmap.bmBitsPixel/8;
    DWORD dwSize=bitmap.bmHeight*bitmap.bmWidthBytes;
    pBits=new BYTE[dwSize];
    GetBitmapBits(hbitmap,dwSize,pBits);
    DeleteObject(hbitmap);
}