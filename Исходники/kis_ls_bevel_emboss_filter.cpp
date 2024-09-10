void KisLsBevelEmbossFilter::applyBevelEmboss(KisPaintDeviceSP srcDevice,
                                              KisMultipleProjection *dst,
                                              const QRect &applyRect,
                                              const psd_layer_effects_bevel_emboss *config,
                                              KisLayerStyleFilterEnvironment *env) const
{
    if (applyRect.isEmpty()) return;

    BevelEmbossRectCalculator d(applyRect, config);

    KisSelectionSP baseSelection = KisLsUtils::selectionFromAlphaChannel(srcDevice, d.initialFetchRect);
    KisPixelSelectionSP selection = baseSelection->pixelSelection();

    //selection->convertToQImage(0, QRect(0,0,300,300)).save("0_selection_initial.png");

    const int size = config->size();

    int limitingGrowSize = 0;
    KisPixelSelectionSP bumpmapSelection = new KisPixelSelection(new KisSelectionEmptyBounds(0));

    switch (config->style()) {
    case psd_bevel_outer_bevel:
        paintBevelSelection(selection, bumpmapSelection, d.applyBevelRect, size, size, false);
        limitingGrowSize = size;
        break;
    case psd_bevel_inner_bevel:
        paintBevelSelection(selection, bumpmapSelection, d.applyBevelRect, size, 0, false);
        limitingGrowSize = 0;
        break;
    case psd_bevel_emboss: {
        const int initialSize = std::ceil(qreal(size) / 2.0);
        paintBevelSelection(selection, bumpmapSelection, d.applyBevelRect, size, initialSize, false);
        limitingGrowSize = initialSize;
        break;
    }
    case psd_bevel_pillow_emboss: {
        const int halfSizeF = std::floor(qreal(size) / 2.0);
        const int halfSizeC = std::ceil(qreal(size) / 2.0);
        // TODO: probably not correct!
        paintBevelSelection(selection, bumpmapSelection, d.applyBevelRect, halfSizeC, halfSizeC, false);
        paintBevelSelection(selection, bumpmapSelection, d.applyBevelRect, halfSizeF, 0, true);
        limitingGrowSize = halfSizeC;
        break;
    }
    case psd_bevel_stroke_emboss:
        warnKrita << "WARNING: Stroke Emboss style is not implemented yet!";
        return;
    }

    KisPixelSelectionSP limitingSelection = new KisPixelSelection(*selection);
    {
        QRect changeRectUnused =
            KisLsUtils::growSelectionUniform(limitingSelection,
                                             limitingGrowSize,
                                             d.applyBevelRect);
        Q_UNUSED(changeRectUnused);
    }

    //bumpmapSelection->convertToQImage(0, QRect(0,0,300,300)).save("1_selection_xconv.png");

    if (config->textureEnabled()) {
        KisPixelSelectionSP textureSelection = new KisPixelSelection(new KisSelectionEmptyBounds(0));

        KisLsUtils::fillPattern(textureSelection, d.applyTextureRect, env,
                                config->textureScale(),
                                config->texturePattern(),
                                config->textureHorizontalPhase(),
                                config->textureVerticalPhase(),
                                config->textureAlignWithLayer());

        int contrastadj = 0;

        {
            using namespace std;

            int tex_depth = config->textureDepth();

            if (tex_depth >= 0.0) {
                if (tex_depth <= 100.0) {
                    contrastadj = int(qRound((1-(tex_depth/100.0)) * -127));
                } else {
                    contrastadj = int(qRound(((tex_depth-100.0)/900.0) * 127));
                }
            } else {
                textureSelection->invert();
                if (tex_depth >= -100.0) {
                    contrastadj = int(qRound((1-(abs(tex_depth)/100.0)) * -127));
                } else {
                    contrastadj = int(qRound(((abs(tex_depth)-100.0)/900.0) * 127));
                }
            }
        }

        qreal contrast = qBound(-1.0, qreal(contrastadj) / 127.0, 1.0);
        mapPixelValues(textureSelection, ContrastOp(contrast), d.applyTextureRect);

        {
            KisPainter gc(bumpmapSelection);
            gc.setCompositeOp(COMPOSITE_MULT);
            gc.bitBlt(d.applyTextureRect.topLeft(), textureSelection, d.applyTextureRect);
            gc.end();
        }
    }

    //bumpmapSelection->convertToQImage(0, QRect(0,0,300,300)).save("15_selection_texture.png");

    if (config->contourEnabled()) {
        if (config->range() != KisLsUtils::FULL_PERCENT_RANGE) {
            KisLsUtils::adjustRange(bumpmapSelection, d.applyContourRect, config->range());
        }

        KisLsUtils::applyContourCorrection(bumpmapSelection,
                                           d.applyContourRect,
                                           config->contourLookupTable(),
                                           config->antiAliased(),
                                           true);
    }

    bumpmap_vals_t bmvals;

    bmvals.azimuth = config->angle();
    bmvals.elevation = config->altitude();
    bmvals.depth = config->depth();
    bmvals.ambient = 0;
    bmvals.compensate = true;
    bmvals.invert = config->direction() == psd_direction_down;
    bmvals.type = LINEAR;

    bumpmap(bumpmapSelection, d.applyBumpmapRect, bmvals);

    //bumpmapSelection->convertToQImage(0, QRect(0,0,300,300)).save("3_selection_bumpmap.png");

    { // TODO: optimize!

        KisLsUtils::applyContourCorrection(bumpmapSelection,
                                           d.applyGlossContourRect,
                                           config->glossContourLookupTable(),
                                           config->glossAntiAliased(),
                                           true);

    }

    if (config->soften()) {
        KisLsUtils::applyGaussian(bumpmapSelection, d.applyGaussianRect, config->soften());
    }


    if (config->textureEnabled() && config->textureInvert()) {
        bumpmapSelection->invert();
    }

    selection->clear();
    mapPixelValues(bumpmapSelection, selection,
                   ShadowsFetchOp(), d.shadowHighlightsFinalRect);
    selection->applySelection(limitingSelection, SELECTION_INTERSECT);

    //dstDevice->convertToQImage(0, QRect(0,0,300,300)).save("4_dst_before_apply.png");
    //selection->convertToQImage(0, QRect(0,0,300,300)).save("4_shadows_sel.png");

    {
        KisPaintDeviceSP dstDevice = dst->getProjection("00_bevel_shadow", config->shadowBlendMode(), srcDevice);

        const KoColor fillColor(config->shadowColor(), dstDevice->colorSpace());
        const QRect &fillRect = d.shadowHighlightsFinalRect;
        KisPaintDeviceSP fillDevice = new KisPaintDevice(dstDevice->colorSpace());
        fillDevice->setDefaultPixel(fillColor);
        KisPainter gc(dstDevice);

        gc.setSelection(baseSelection);
        gc.setCompositeOp(COMPOSITE_OVER);
        env->setupFinalPainter(&gc, config->shadowOpacity(), QBitArray());
        gc.bitBlt(fillRect.topLeft(), fillDevice, fillRect);
        gc.end();
    }

    selection->clear();
    mapPixelValues(bumpmapSelection, selection,
                   HighlightsFetchOp(), d.shadowHighlightsFinalRect);
    selection->applySelection(limitingSelection, SELECTION_INTERSECT);

    //selection->convertToQImage(0, QRect(0,0,300,300)).save("5_highlights_sel.png");

    {
        KisPaintDeviceSP dstDevice = dst->getProjection("01_bevel_highlight", config->highlightBlendMode(), srcDevice);

        const KoColor fillColor(config->highlightColor(), dstDevice->colorSpace());
        const QRect &fillRect = d.shadowHighlightsFinalRect;
        KisPaintDeviceSP fillDevice = new KisPaintDevice(dstDevice->colorSpace());
        fillDevice->setDefaultPixel(fillColor);
        KisPainter gc(dstDevice);
        gc.setSelection(baseSelection);
        gc.setCompositeOp(COMPOSITE_OVER);
        env->setupFinalPainter(&gc, config->highlightOpacity(), QBitArray());
        gc.bitBlt(fillRect.topLeft(), fillDevice, fillRect);
        gc.end();
    }
}