//*******************************************************************************
void CBCGPKnob::CreatePointerPoints(double dblRadius,
                                    CBCGPPointsArray& arPoints,
                                    int nPointerIndex, BOOL bShadow)
{
    if (m_rect.IsRectEmpty())
    {
        return;
    }

    CBCGPRect rect = m_rect;

    CBCGPKnobPointer* pData = DYNAMIC_DOWNCAST(CBCGPKnobPointer, m_arData[nPointerIndex]);
    if (pData == NULL)
    {
        ASSERT(FALSE);
        return;
    }

    CBCGPCircularGaugeScale* pScale = GetScale(pData->GetScale());
    if (pScale == NULL)
    {
        ASSERT(FALSE);
        return;
    }

    const double scaleRatio = GetScaleRatioMid();

    double dblValue = pData->IsAnimated() ? pData->GetAnimatedValue() : pData->GetValue();

    double dblOffset = bcg_clamp(pData->GetOffsetFromCenter(), 0.0, 1.0);
    if (dblOffset == 0.0)
    {
        dblOffset = dblRadius * .5;
    }
    else
    {
        dblOffset = dblRadius * bcg_clamp(dblOffset, 0.5, 1.0);
    }

    double dblAngle = bcg_deg2rad(pScale->GetStartAngle()) - bcg_deg2rad(pScale->GetStartAngle() - pScale->GetFinishAngle()) * (dblValue - pScale->GetStart()) / (pScale->GetFinish() - pScale->GetStart());
    dblAngle = bcg_normalize_rad (dblAngle);

    if (bShadow)
    {
        rect.OffsetRect(2 * m_sizeScaleRatio.cx, 2 * m_sizeScaleRatio.cy);
    }

    CBCGPPoint center((rect.left + rect.right) / 2.0, (rect.top + rect.bottom) / 2.0);

    const double angleCos  = cos(dblAngle);
    const double angleSin  = sin(dblAngle);

    double dblWidth = bcg_clamp(pData->GetWidth(), 0.0, dblRadius / 10.0);
    const double dblPointerAngle = dblAngle - M_PI_2;

    switch (pData->GetStyle())
    {
    case CBCGPKnobPointer::BCGP_KNOB_POINTER_HANDLE:
    {
        dblRadius -= .2 * scaleRatio;
        double dblExtend = (dblRadius * .9);
        double dblSize = dblRadius + dblExtend;
        center.x -= angleCos * dblExtend;
        center.y += angleSin * dblExtend;

        if (dblWidth == 0.0)
        {
            dblWidth = dblRadius / 3.0;
        }

        dblWidth *= 0.5;

        if (dblWidth < 1.0)
        {
            arPoints.Add(center);

            arPoints.Add(CBCGPPoint(
                             center.x + angleCos * dblSize,
                             center.y - angleSin * dblSize));
        }
        else
        {
            double dblArrowLen = max(2.0 * dblWidth, 10.0 * scaleRatio);
            dblSize -= dblArrowLen;

            const double dx = cos(dblPointerAngle) * dblWidth;
            const double dy = -sin(dblPointerAngle) * dblWidth;

            arPoints.Add(CBCGPPoint(center.x + dx, center.y + dy));

            arPoints.Add(CBCGPPoint(center.x - dx, center.y - dy));

            const CBCGPPoint pt1(
                center.x + angleCos * dblSize - dx,
                center.y - angleSin * dblSize - dy);

            const CBCGPPoint pt2(
                center.x + angleCos * dblSize + dx,
                center.y - angleSin * dblSize + dy);

            arPoints.Add(pt1);

            arPoints.Add(CBCGPPoint(
                             center.x + angleCos * (dblSize + dblArrowLen),
                             center.y - angleSin * (dblSize + dblArrowLen)));

            arPoints.Add(pt2);
        }
    }
    break;

    case CBCGPKnobPointer::BCGP_KNOB_POINTER_LINE:
    {
        if (bShadow)
        {
            return;
        }

        if (dblWidth == 0.0)
        {
            dblWidth = 2. * scaleRatio;
        }

        const double dx = cos(dblPointerAngle) * dblWidth;
        const double dy = -sin(dblPointerAngle) * dblWidth;

        arPoints.Add(CBCGPPoint(center.x + angleCos * dblOffset - dx, center.y - angleSin * dblOffset - dy));
        arPoints.Add(CBCGPPoint(center.x + angleCos * dblOffset + dx, center.y - angleSin * dblOffset + dy));

        dblOffset = dblRadius - 4. * scaleRatio;

        arPoints.Add(CBCGPPoint(center.x + angleCos * dblOffset + dx, center.y - angleSin * dblOffset + dy));
        arPoints.Add(CBCGPPoint(center.x + angleCos * dblOffset - dx, center.y - angleSin * dblOffset - dy));
    }
    break;

    case CBCGPKnobPointer::BCGP_KNOB_POINTER_CIRCLE:
    {
        if (bShadow)
        {
            return;
        }

        if (dblWidth == 0.0)
        {
            dblWidth = max(2. * scaleRatio, dblRadius / 8);
        }

        dblOffset = dblRadius - 6. * scaleRatio - dblWidth;

        arPoints.Add(CBCGPPoint(center.x + angleCos * dblOffset, center.y - angleSin * dblOffset));
        arPoints.Add(CBCGPPoint(dblWidth, dblWidth));
    }
    break;
    }
}