void DistortionFXFilter::fisheyeMultithreaded(const Args& prm)
{
    int Width       = prm.orgImage->width();
    int Height      = prm.orgImage->height();
    uchar* data     = prm.orgImage->bits();
    bool sixteenBit = prm.orgImage->sixteenBit();
    int bytesDepth  = prm.orgImage->bytesDepth();
    uchar* pResBits = prm.destImage->bits();

    double nh, nw, tw;

    DColor color;
    int offset;

    int nHalfW         = Width  / 2;
    int nHalfH         = Height / 2;
    double lfXScale    = 1.0;
    double lfYScale    = 1.0;
    double lfCoeffStep = prm.Coeff / 1000.0;
    double lfRadius, lfAngle;

    if (Width > Height)
    {
        lfYScale = (double)Width / (double)Height;
    }
    else if (Height > Width)
    {
        lfXScale = (double)Height / (double)Width;
    }

    double lfRadMax = (double)qMax(Height, Width) / 2.0;
    double lfCoeff  = lfRadMax / qLn(qFabs(lfCoeffStep) * lfRadMax + 1.0);
    double th       = lfYScale * (double)(prm.h - nHalfH);

    for (int w = prm.start; runningFlag() && (w < prm.stop); ++w)
    {
        tw = lfXScale * (double)(w - nHalfW);

        // we find the distance from the center
        lfRadius = qSqrt(th * th + tw * tw);

        if (lfRadius < lfRadMax)
        {
            lfAngle = qAtan2(th, tw);

            if (prm.Coeff > 0.0)
            {
                lfRadius = (qExp(lfRadius / lfCoeff) - 1.0) / lfCoeffStep;
            }
            else
            {
                lfRadius = lfCoeff * qLn(1.0 + (-1.0 * lfCoeffStep) * lfRadius);
            }

            nw = (double)nHalfW + (lfRadius / lfXScale) * qCos(lfAngle);
            nh = (double)nHalfH + (lfRadius / lfYScale) * qSin(lfAngle);

            setPixelFromOther(Width, Height, sixteenBit, bytesDepth, data, pResBits, w, prm.h, nw, nh, prm.AntiAlias);
        }
        else
        {
            // copy pixel
            offset = getOffset(Width, w, prm.h, bytesDepth);
            color.setColor(data + offset, sixteenBit);
            color.setPixel(pResBits + offset);
        }
    }
}