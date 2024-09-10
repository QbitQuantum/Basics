/*--------------------------------------------------------------------------*/
void PegGroup::Draw(void)
{
    #ifdef PEG_UNICODE
    PEGCHAR cTest[2] = {'E', '\0'};
    #else
    PEGCHAR cTest[] = "E";
    #endif

    if (Parent())
    {
        muColors[PCI_NORMAL] = Parent()->muColors[PCI_NORMAL];
    }
    BeginDraw();

    PegColor Color(muColors[PCI_NORMAL], muColors[PCI_NORMAL], CF_FILL);
    Rectangle(mClient, Color, 0);

    Color.Set(PCLR_LOWLIGHT, PCLR_LOWLIGHT, CF_NONE);
    
    Color.uForeground = PCLR_LOWLIGHT;
    SIGNED iTextLeft = mReal.wLeft + TextWidth(cTest, mpFont);
    SIGNED iTextRight = iTextLeft + TextWidth(mpText, mpFont) + 4;

    if(mpText)
    {
        Line(mReal.wLeft, mClient.wTop - 2, iTextLeft,
            mClient.wTop - 2, Color);
        Line(iTextRight, mClient.wTop - 2, mReal.wRight,
            mClient.wTop - 2, Color);
    }
    else
    {
        Line(mReal.wLeft, mClient.wTop - 2, mReal.wRight,
             mClient.wTop - 2, Color);
    }
    Line(mReal.wLeft, mClient.wTop - 1, mReal.wLeft,
        mReal.wBottom, Color);
    Line(mReal.wLeft + 1, mReal.wBottom - 1,
        mReal.wRight - 1, mReal.wBottom - 1, Color);
    Line(mReal.wRight - 1, mClient.wTop - 2,
        mReal.wRight - 1, mReal.wBottom - 1, Color);

    Color.uForeground = PCLR_HIGHLIGHT;
    if(mpText)
    {
        Line(mReal.wLeft + 1, mClient.wTop - 1, iTextLeft,
            mClient.wTop - 1, Color);
        Line(iTextRight, mClient.wTop - 1, mReal.wRight - 2,
            mClient.wTop - 1, Color);
    }
    else
    {
        Line(mReal.wLeft + 1, mClient.wTop - 1, mReal.wRight - 2,
             mClient.wTop - 1, Color);
    }
    Line(mReal.wLeft + 1, mClient.wTop, mReal.wLeft + 1,
        mReal.wBottom - 1, Color);
    Line(mReal.wLeft, mReal.wBottom, mReal.wRight,
        mReal.wBottom, Color);
    Line(mReal.wRight, mClient.wTop - 2, mReal.wRight,
        mReal.wBottom, Color);

    if(mpText)
    {
        if (mwStyle & AF_ENABLED)
        {
            Color.uForeground = muColors[PCI_NTEXT];
        }
        else
        {
            Color.uForeground = PCLR_LOWLIGHT;
        }
        PegPoint Put;
        Put.x = iTextLeft + 2;
        Put.y = mReal.wTop;

        DrawText(Put, mpText, Color, mpFont);
    }

    PegThing::Draw();       // to draw children
    EndDraw();
}