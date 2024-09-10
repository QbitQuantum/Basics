/*
 * Draw a line from top-left to bottom-right
 */
static void FASTCALL
vgaNWtoSE(
    IN CLIPOBJ* Clip,
    IN BRUSHOBJ* Brush,
    IN LONG x,
    IN LONG y,
    IN LONG deltax,
    IN LONG deltay)
{
    int i;
    int error;
    BOOLEAN EnumMore;
    PRECTL ClipRect;
    RECT_ENUM RectEnum;
    ULONG Pixel = Brush->iSolidColor;
    LONG delta;

    CLIPOBJ_cEnumStart(Clip, FALSE, CT_RECTANGLES, CD_RIGHTDOWN, 0);
    EnumMore = CLIPOBJ_bEnum(Clip, (ULONG) sizeof(RectEnum), (PVOID) &RectEnum);
    ClipRect = RectEnum.arcl;
    delta = max(deltax, deltay);
    i = 0;
    error = delta / 2;
    while (i < delta && (ClipRect < RectEnum.arcl + RectEnum.c || EnumMore))
    {
        while ((ClipRect < RectEnum.arcl + RectEnum.c /* there's still a current clip rect */
                && (ClipRect->bottom <= y             /* but it's above us */
                    || (ClipRect->top <= y && ClipRect->right <= x))) /* or to the left of us */
               || EnumMore)                           /* no current clip rect, but rects left */
        {
            /* Skip to the next clip rect */
            if (RectEnum.arcl + RectEnum.c <= ClipRect)
            {
                EnumMore = CLIPOBJ_bEnum(Clip, (ULONG) sizeof(RectEnum), (PVOID) &RectEnum);
                ClipRect = RectEnum.arcl;
            }
            else
            {
                ClipRect++;
            }
        }
        if ( ClipRect < RectEnum.arcl + RectEnum.c ) /* If there's no current clip rect we're done */
        {
            if (ClipRect->left <= x && ClipRect->top <= y)
                vgaPutPixel ( x, y, Pixel );
            if ( deltax < deltay )
            {
                y++;
                error += deltax;
                if ( error >= deltay )
                {
                    x++;
                    error -= deltay;
                }
            }
            else
            {
                x++;
                error += deltay;
                if ( error >= deltax )
                {
                    y++;
                    error -= deltax;
                }
            }
            i++;
        }
    }
}