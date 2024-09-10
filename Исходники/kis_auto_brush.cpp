void KisAutoBrush::generateMaskAndApplyMaskOrCreateDab(KisFixedPaintDeviceSP dst,
        KisBrush::ColoringInformation* coloringInformation,
        double scaleX, double scaleY, double angle,
        const KisPaintInformation& info,
        double subPixelX , double subPixelY, qreal softnessFactor) const
{
    Q_UNUSED(info);

    // Generate the paint device from the mask
    const KoColorSpace* cs = dst->colorSpace();
    quint32 pixelSize = cs->pixelSize();

    // mask dimension methods already includes KisBrush::angle()
    int dstWidth = maskWidth(scaleX, angle, subPixelX, subPixelY, info);
    int dstHeight = maskHeight(scaleY, angle, subPixelX, subPixelY, info);
    QPointF hotSpot = this->hotSpot(scaleX, scaleY, angle, info);

    // mask size and hotSpot function take the KisBrush rotation into account
    angle += KisBrush::angle();

    // if there's coloring information, we merely change the alpha: in that case,
    // the dab should be big enough!
    if (coloringInformation) {

        // old bounds
        QRect oldBounds = dst->bounds();

        // new bounds. we don't care if there is some extra memory occcupied.
        dst->setRect(QRect(0, 0, dstWidth, dstHeight));

        if (dstWidth * dstHeight <= oldBounds.width() * oldBounds.height()) {
            // just clear the data in dst,
            memset(dst->data(), OPACITY_TRANSPARENT_U8, dstWidth * dstHeight * dst->pixelSize());
        } else {
            // enlarge the data
            dst->initialize();
        }
    } else {
        if (dst->data() == 0 || dst->bounds().isEmpty()) {
            qWarning() << "Creating a default black dab: no coloring info and no initialized paint device to mask";
            dst->clear(QRect(0, 0, dstWidth, dstHeight));
        }
        Q_ASSERT(dst->bounds().width() >= dstWidth && dst->bounds().height() >= dstHeight);
    }

    quint8* dabPointer = dst->data();

    quint8* color = 0;
    if (coloringInformation) {
        if (dynamic_cast<PlainColoringInformation*>(coloringInformation)) {
            color = const_cast<quint8*>(coloringInformation->color());
        }
    }

    double invScaleX = 1.0 / scaleX;
    double invScaleY = 1.0 / scaleY;

    double centerX = hotSpot.x() - 0.5 + subPixelX;
    double centerY = hotSpot.y() - 0.5 + subPixelY;

    d->shape->setSoftness( softnessFactor );

    if (coloringInformation) {
        if (color && pixelSize == 4) {
            fillPixelOptimized_4bytes(color, dabPointer, dstWidth * dstHeight);
        } else if (color) {
            fillPixelOptimized_general(color, dabPointer, dstWidth * dstHeight, pixelSize);
        } else {
            for (int y = 0; y < dstHeight; y++) {
                for (int x = 0; x < dstWidth; x++) {
                    memcpy(dabPointer, coloringInformation->color(), pixelSize);
                    coloringInformation->nextColumn();
                    dabPointer += pixelSize;
                }
                coloringInformation->nextRow();
            }
        }
    }

    MaskProcessingData data(dst, cs, d->randomness, d->density,
                            centerX, centerY,
                            invScaleX, invScaleY,
                            angle);

    KisBrushMaskApplicatorBase *applicator = d->shape->applicator();
    applicator->initializeData(&data);

    int jobs = d->idealThreadCountCached;
    if(dstHeight > 100 && jobs >= 4) {
        int splitter = dstHeight/jobs;
        QVector<QRect> rects;
        for(int i = 0; i < jobs - 1; i++) {
            rects << QRect(0, i*splitter, dstWidth, splitter);
        }
        rects << QRect(0, (jobs - 1)*splitter, dstWidth, dstHeight - (jobs - 1)*splitter);
        OperatorWrapper wrapper(applicator);
        QtConcurrent::blockingMap(rects, wrapper);
    } else {
        QRect rect(0, 0, dstWidth, dstHeight);
        applicator->process(rect);
    }
}