//
//    Clip a card SHAPE - basically any rectangle
//  with rounded corners
//
int ClipCard(HDC hdc, int x, int y, int width, int height)
{
    ExcludeClipRect(hdc, x+2,        y,     x+2+width-4, y+  height);
    ExcludeClipRect(hdc, x,            y+2, x+1,          y+2+height-4);
    ExcludeClipRect(hdc, x+1,        y+1, x+2,          y+1+height-2);
    ExcludeClipRect(hdc, x+width-2, y+1, x+width-2+1, y+1+height-2);
    ExcludeClipRect(hdc, x+width-1, y+2, x+width-1+1, y+2+height-4);
    return 0;
}