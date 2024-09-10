qreal KisFilterOp::paintAt(const KisPaintInformation& info)
{
    if (!painter()) {
        return 1.0;
    }

    if (!m_filter) {
        return 1.0;
    }

    if (!source()) {
        return 1.0;
    }

    KisBrushSP brush = m_brush;;
    if (!brush) return 1.0;

    if (! brush->canPaintFor(info))
        return 1.0;

    qreal scale = KisPaintOp::scaleForPressure(m_sizeOption.apply(info));
    if ((scale * brush->width()) <= 0.01 || (scale * brush->height()) <= 0.01) return spacing(scale);

    setCurrentScale(scale);
    
    QPointF hotSpot = brush->hotSpot(scale, scale);
    QPointF pt = info.pos() - hotSpot;


    // Split the coordinates into integer plus fractional parts. The integer
    // is where the dab will be positioned and the fractional part determines
    // the sub-pixel positioning.
    qint32 x;
    qreal xFraction;
    qint32 y;
    qreal yFraction;

    splitCoordinate(pt.x(), &x, &xFraction);
    splitCoordinate(pt.y(), &y, &yFraction);

    qint32 maskWidth = brush->maskWidth(scale, 0.0);
    qint32 maskHeight = brush->maskHeight(scale, 0.0);

    // Filter the paint device
    m_filter->process(KisConstProcessingInformation(source(), QPoint(x, y)),
                    KisProcessingInformation(m_tmpDevice, QPoint(0, 0)),
                    QSize(maskWidth, maskHeight),
                    m_filterConfiguration, 0);

    // Apply the mask on the paint device (filter before mask because edge pixels may be important)

    KisFixedPaintDeviceSP fixedDab = new KisFixedPaintDevice(m_tmpDevice->colorSpace());
    fixedDab->setRect(m_tmpDevice->extent());
    fixedDab->initialize();

    m_tmpDevice->readBytes(fixedDab->data(), fixedDab->bounds());
    brush->mask(fixedDab, scale, scale, 0.0, info, xFraction, yFraction);
    m_tmpDevice->writeBytes(fixedDab->data(), fixedDab->bounds());

    if (!m_ignoreAlpha) {
        KisHLineIteratorPixel itTmpDev = m_tmpDevice->createHLineIterator(0, 0, maskWidth);
        KisHLineIteratorPixel itSrc = source()->createHLineIterator(x, y, maskWidth);
        const KoColorSpace* cs = m_tmpDevice->colorSpace();
        for (int y = 0; y < maskHeight; ++y) {
            while (!itTmpDev.isDone()) {
                quint8 alphaTmpDev = cs->opacityU8(itTmpDev.rawData());
                quint8 alphaSrc = cs->opacityU8(itSrc.rawData());

                cs->setOpacity(itTmpDev.rawData(), qMin(alphaTmpDev, alphaSrc), 1);
                ++itTmpDev;
                ++itSrc;
            }
            itTmpDev.nextRow();
            itSrc.nextRow();
        }
    }

    // Blit the paint device onto the layer
    QRect dabRect = QRect(0, 0, maskWidth, maskHeight);
    QRect dstRect = QRect(x, y, dabRect.width(), dabRect.height());

    if (dstRect.isNull() || dstRect.isEmpty() || !dstRect.isValid()) return 1.0;

    qint32 sx = dstRect.x() - x;
    qint32 sy = dstRect.y() - y;
    qint32 sw = dstRect.width();
    qint32 sh = dstRect.height();

    painter()->bitBlt(dstRect.x(), dstRect.y(), m_tmpDevice, sx, sy, sw, sh);
    return spacing(scale);
}