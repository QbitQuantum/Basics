static void paint(void *widget, OsdPainter *painter, int x, int y)
{        
    WgVerticalGauge *self = widget;
    osdPainterTranslate(painter, x, y);
    osdPainterSetPen(painter, &gaugePen);
    osdPainterSetBrush(painter, &gaugeBrush);
    osdPainterDrawLine(painter, 0, -GAUGE_HEIGHT / 2, 0, GAUGE_HEIGHT / 2);

    // draw scale
    osdPainterSetFont(painter, osdFontByName("consolas10"));
    float rem = fmodf(self->value, self->scale);
    int offset = (int)((rem / self->scale) * LONG_NOTCH_SPACE);
    float centerNotchVal =self->scale * ((int)(self->value / self->scale));
    float upNotchVal = centerNotchVal;
    float downNotchVal = upNotchVal;
    int ygamut = 0;
    while(1) {
        bool longNotch = (((ygamut) % LONG_NOTCH_SPACE) == 0);
        int notchLen = (longNotch) ? LONG_NOTCH_LEN : SHORT_NOTCH_LEN;
        if (self->leftSide) notchLen = -notchLen;
        if ((ygamut + offset) <= (GAUGE_HEIGHT / 2)) {
            if ((!self->noNegative) || (downNotchVal >= 0)) {
                osdPainterDrawLine(painter, 0, ygamut + offset, notchLen, ygamut + offset);
                // draw notch caption (lower)
                if (longNotch) {
                    char strVal[8];
                    itoa((int)downNotchVal, strVal, 10);
                    int textX;
                    if (self->leftSide) {
                        int width = 0;
                        int height = 0;
                        osdPainterTextBounds(painter, strVal, &width, &height);
                        textX = -LONG_NOTCH_LEN - 2 - width;
                    } else {
                        textX = LONG_NOTCH_LEN + 2;
                    }
                    osdPainterDrawText(painter, textX, ygamut + offset - 5, strVal);
                }
            }
            if (longNotch) downNotchVal -= self->scale;
        }
        if ((-ygamut + offset) < (-GAUGE_HEIGHT / 2)) break;

        osdPainterDrawLine(painter, 0, -ygamut + offset, notchLen, -ygamut + offset);

        // draw notch caption (upper)
        if (longNotch) {
            char strVal[8];
            itoa((int)upNotchVal, strVal, 10);
            upNotchVal += self->scale;
            int textX;
            if (self->leftSide) {
                int width = 0;
                int height = 0;
                osdPainterTextBounds(painter, strVal, &width, &height);
                textX = -LONG_NOTCH_LEN - 2 - width;
            } else {
                textX = LONG_NOTCH_LEN + 2;
            }
            osdPainterDrawText(painter, textX, -ygamut + offset - 5, strVal);
        }
        ygamut += SHORT_NOTCH_SPACE;
    }

    // draw arrow with value
    char strVal[12];
    if (fabsf(self->value) < 10) {
        if (self->value < 0)
            lsprintf(strVal, "-%d.%d", (int)fabsf(self->value),
                    (int)fabsf(self->value * 10) % 10);
        else
            lsprintf(strVal, "%d.%d", (int)fabsf(self->value),
                    (int)fabsf(self->value * 10) % 10);
    } else {
        itoa((int)self->value, strVal, 10);
    }
    int width = 0;
    int height = 0;
    osdPainterSetFont(painter, osdFontByName(needleFont));
    osdPainterTextBounds(painter, strVal, &width, &height);

    int textValueX = 0;
    int textUnitX = 0;
    int poly[10];
    if (!self->leftSide) {
        poly[0] = 1; poly[1] =  0;
        poly[2] = NEEDLE_LENGTH; poly[3] =  -height / 2 - 1;
        poly[4] = NEEDLE_LENGTH + width + 1; poly[5] =  -height / 2 -1;
        poly[6] = NEEDLE_LENGTH + width + 1; poly[7] = height / 2 + 1;
        poly[8] = NEEDLE_LENGTH;  poly[9] = height / 2 +1;
        textValueX = NEEDLE_LENGTH + 1;
        textUnitX = LONG_NOTCH_LEN + 28;
    } else {
        poly[0] = -1; poly[1] =  0;
        poly[2] = -NEEDLE_LENGTH; poly[3] =  -height / 2 - 1;
        poly[4] = -NEEDLE_LENGTH - width - 1; poly[5] =  -height / 2 -1;
        poly[6] = -NEEDLE_LENGTH - width - 1; poly[7] = height / 2 + 1;
        poly[8] = -NEEDLE_LENGTH;  poly[9] = height / 2 +1;

        textValueX = - NEEDLE_LENGTH - width + 1;
        textUnitX = - LONG_NOTCH_LEN - 45;

    }

    osdPainterSetPen(painter, &needlePen);
    osdPainterSetBrush(painter, &needleBrush);
    osdPainterDrawPoly(painter, poly, 5);
    osdPainterSetBrush(painter, &gaugeBrush);
    osdPainterSetPen(painter, &textPen);
    osdPainterDrawText(painter, textValueX, -height / 2 + 1, strVal);
    osdPainterSetFont(painter, osdFontByName(captionFont));
    osdPainterDrawText(painter, textUnitX, 12, self->units);
}