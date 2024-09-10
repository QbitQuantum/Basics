void applyDropShadow(KisPaintDeviceSP srcDevice,
                     KisPaintDeviceSP dstDevice,
                     const QRect &applyRect,
                     const psd_layer_effects_context *context,
                     const psd_layer_effects_shadow_base *shadow,
                     const KisLayerStyleFilterEnvironment *env)
{
    if (applyRect.isEmpty()) return;

    ShadowRectsData d(applyRect, context, shadow, ShadowRectsData::NEED_RECT);

    KisSelectionSP baseSelection =
        KisLsUtils::selectionFromAlphaChannel(srcDevice, d.spreadNeedRect);

    KisPixelSelectionSP selection = baseSelection->pixelSelection();

    //selection->convertToQImage(0, QRect(0,0,300,300)).save("0_selection_initial.png");

    if (shadow->invertsSelection()) {
        selection->invert();
    }

    /**
     * Copy selection which will be erased from the original later
     */
    KisPixelSelectionSP knockOutSelection;
    if (shadow->knocksOut()) {
        knockOutSelection = new KisPixelSelection(*selection);
    }

    if (shadow->technique() == psd_technique_precise) {
        KisLsUtils::findEdge(selection, d.blurNeedRect, true);
    }

    /**
     * Spread and blur the selection
     */
    if (d.spread_size) {
        KisLsUtils::applyGaussian(selection, d.blurNeedRect, d.spread_size);

        // TODO: find out why in libpsd we pass false here. If we do so,
        //       the result is fully black, which is not expected
        KisLsUtils::findEdge(selection, d.blurNeedRect, true /*shadow->edgeHidden()*/);
    }

    //selection->convertToQImage(0, QRect(0,0,300,300)).save("1_selection_spread.png");

    if (d.blur_size) {
        KisLsUtils::applyGaussian(selection, d.noiseNeedRect, d.blur_size);
    }
    //selection->convertToQImage(0, QRect(0,0,300,300)).save("2_selection_blur.png");

    if (shadow->range() != KisLsUtils::FULL_PERCENT_RANGE) {
        KisLsUtils::adjustRange(selection, d.noiseNeedRect, shadow->range());
    }

    const psd_layer_effects_inner_glow *iglow = 0;
    if ((iglow =
         dynamic_cast<const psd_layer_effects_inner_glow *>(shadow)) &&
        iglow->source() == psd_glow_center) {

        selection->invert();
    }

    /**
     * Contour correction
     */
    KisLsUtils::applyContourCorrection(selection,
                                       d.noiseNeedRect,
                                       shadow->contourLookupTable(),
                                       shadow->antiAliased(),
                                       shadow->edgeHidden());

    //selection->convertToQImage(0, QRect(0,0,300,300)).save("3_selection_contour.png");

    /**
     * Noise
     */
    if (shadow->noise() > 0) {
        KisLsUtils::applyNoise(selection,
                               d.srcRect,
                               shadow->noise(),
                               context);
    }
    //selection->convertToQImage(0, QRect(0,0,300,300)).save("4_selection_noise.png");

    if (!d.offset.isNull()) {
        selection->setX(d.offset.x());
        selection->setY(d.offset.y());
    }

    /**
     * Knock-out original outline of the device from the resulting shade
     */
    if (shadow->knocksOut()) {
        KIS_ASSERT_RECOVER_RETURN(knockOutSelection);

        QRect knockOutRect = !shadow->invertsSelection() ?
            d.srcRect : d.spreadNeedRect;

        knockOutRect &= d.dstRect;

        KisPainter gc(selection);
        gc.setCompositeOp(COMPOSITE_ERASE);
        gc.bitBlt(knockOutRect.topLeft(), knockOutSelection, knockOutRect);
    }
    //selection->convertToQImage(0, QRect(0,0,300,300)).save("5_selection_knockout.png");

    KisLsUtils::applyFinalSelection(baseSelection,
                                    srcDevice,
                                    dstDevice,
                                    d.srcRect,
                                    d.dstRect,
                                    context,
                                    shadow,
                                    env);
}